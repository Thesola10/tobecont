# Makefile for tobecontinued
BACKEND := x11
         # one of x11, win32, quartz

CFLAGS  := $(shell pkg-config --cflags sdl2) -DBACKEND=$(BACKEND)

LDFLAGS := -fPIC
LDLIBS  := $(shell pkg-config --libs sdl2) -lm

ifeq ($(BACKEND),x11)
  LDLIBS += $(shell pkg-config --libs x11)
endif

OBJFMT  := elf64-x86-64

OUTPUT  := tobecont
SOURCES  = src/main.c \
		   src/$(BACKEND)/screenshot.c
ASSETS   = assets/arr.bmp \
           assets/tbc.wav

OBJS     = $(patsubst %.c,%.c.o,$(SOURCES))
ASSETO   = $(patsubst %,%.raw.o,$(ASSETS))

ifeq ($(BACKEND),win32)
  OBJS += assets/tobecont.exe.res
endif


$(OUTPUT): $(OBJS) $(ASSETO)
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

%.c.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.raw.o: %
	$(OBJCOPY) -I binary -O $(OBJFMT) $< $@

%.res: %.rc
	$(WINDRES) $< -O coff -o $@
