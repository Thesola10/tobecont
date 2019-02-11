# Makefile for tobecontinued

CC       = gcc
CC_FLAGS = $(shell pkgconf --cflags --libs sdl2 x11) -lm -ggdb

OUTPUT   = tobecont
ASSETS   = assets/arr.bmp \
           assets/tbc.wav

SRC      = $(wildcard src/*.c)

$(OUTPUT): $(SRC) $(ASSETS) src/assets_link.s
	$(CC) $(CC_FLAGS) src/assets_link.s $(SRC) -o $@

