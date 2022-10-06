# Makefile for tobecontinued

CC       = gcc
CFLAGS   = $(shell pkg-config --cflags sdl2 x11)

LD       = gcc
LDFLAGS  = -fPIC
LDLIBS   = $(shell pkg-config --libs sdl2 x11) -lm

OBJCOPY  = objcopy
OBJFMT   = elf64-x86-64

OUTPUT   = tobecont
SOURCES  = src/main.c
ASSETS   = assets/arr.bmp \
           assets/tbc.wav

OBJS     = $(patsubst %.c,%.c.o,$(SOURCES))
ASSETO   = $(patsubst %,%.raw.o,$(ASSETS))


$(OUTPUT): $(OBJS) $(ASSETO)
	$(LD) $(LDFLAGS) $^ -o $@ $(LDLIBS)

%.c.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.raw.o: %
	$(OBJCOPY) -I binary -O $(OBJFMT) $< $@
