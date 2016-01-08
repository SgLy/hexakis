SDL_CFLAGS=`sdl2-config --cflags`
SDL_LIBS=`sdl2-config --libs`

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

hexakis: $(GUI_OBJS) $(LIB_OBJS)
	$(CXXLD) $(SDL_LIBS) $(GUI_OBJS) $(LIB_OBJS) -o hexakis

dirty_test: test/dirty_test.o $(LIB_OBJS)
	$(CXXLD) $(LIB_OBJS) test/dirty_test.o -o dirty_test

-include $(LIB_DEPS) $(GUI_DEPS)

clean:
	rm -f $(LIB_OBJS) $(GUI_OBJS) $(LIB_DEPS) $(GUI_DEPS) hexakis dirty_test

.PHONY: all clean
