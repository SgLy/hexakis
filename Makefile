SDL_CFLAGS="`sdl2-config --cflags`"
SDL_LIBS="`sdl2-config --libs`"

CC=gcc
CXX=g++

CXXLD=g++

CFLAGS=$(SDL_CFLAGS) -MMD -MP
CXXFLAGS=$(SDL_CFLAGS) -MMD -MP -std=gnu++11

GUI_CPPSRCS=$(wildcard gui/*.cpp)
GUI_OBJS=$(GUI_CPPSRCS:.cpp=.o)
GUI_DEPS=$(GUI_CPPSRCS:.cpp=.d)

LIB_CPPSRCS=$(wildcard lib/*.cpp)
LIB_OBJS=$(LIB_CPPSRCS:.cpp=.o)
LIB_DEPS=$(LIB_CPPSRCS:.cpp=.d)

all: hexakis

hexakis: $(GUI_OBJS) lib/libhexakis.a
	$(CXXLD) $(SDL_LIBS) $(GUI_OBJS) lib/libhexakis.a -o hexakis

lib/libhexakis.a: $(LIB_OBJS)
	rm -f lib/libhexakis.a
	ar r lib/libhexakis.a $(LIB_OBJS)
	ranlib lib/libhexakis.a

dirty_test: lib/libhexakis.a
	$(CXXLD) $(CXXFLAGS) lib/libhexakis.a test/dirty_test.cpp -o dirty_test

-include $(LIB_DEPS) $(GUI_DEPS)

clean:
	rm -f $(LIB_OBJS) $(GUI_OBJS) $(LIB_DEPS) $(GUI_DEPS) hexakis lib/libhexakis.a dirty_test

.PHONY: all clean
