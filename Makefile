SDL_CFLAGS="`sdl2-config --cflags`"
SDL_LIBS="`sdl2-config --libs`"

CC=gcc
CXX=g++

CXXLD=g++

CFLAGS=$(SDL_CFLAGS)

GUI_OBJS=gui/main.o

LIB_OBJS=

all: hexakis

hexakis: $(GUI_OBJS)
	$(CXXLD) $(SDL_LIBS) $(GUI_OBJS) -o hexakis

lib/libhexakis.a: $(LIB_OBJS)

.PHONY: all
