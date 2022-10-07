# Makefile for tobecontinued
BACKEND := x11
         # one of x11, win32, quartz

CFLAGS  := $(shell pkg-config --cflags sdl2) -DBACKEND=$(BACKEND)

LDFLAGS := -fPIC
LDLIBS  := $(shell pkg-config --libs sdl2) -lm

ifeq ($(BACKEND),x11)
  LDLIBS += $(shell pkg-config --libs x11)
endif

ifndef OBJCOPY
OBJCOPY := objcopy
endif

OBJFMT  := elf64-x86-64

O       := .
OUTPUT  := $(O)/tobecont
SOURCES  = src/main.c \
		   src/$(BACKEND)/screenshot.c
ASSETS   = assets/arr.bmp \
           assets/tbc.wav

OBJS     = $(patsubst %.c,$(O)/%.c.o,$(SOURCES))
ASSETO   = $(patsubst %,$(O)/%.raw.o,$(ASSETS))

ifeq ($(BACKEND),win32)
  OBJS += assets/tobecont.exe.res
endif

## Build tobecont binary
all: $(OUTPUT)

## Clean up and rebuild
re:: fclean
re:: all

$(OUTPUT): $(OBJS) $(ASSETO)
	@mkdir -p $(@D)
	@$(call rich_echo,"LD","$(OUTPUT)")
	@$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

$(O)/%.c.o: %.c
	@mkdir -p $(@D)
	@$(call rich_echo,"CC","$@")
	@$(CC) $(CFLAGS) -c $< -o $@

$(O)/%.raw.o: %
	@mkdir -p $(@D)
	@$(call rich_echo,"OBJCOPY","$@")
	@$(OBJCOPY) -I binary -O $(OBJFMT) $< $@

$(O)/%.res: %.rc
	@mkdir -p $(@D)
	@$(call rich_echo,"WINDRES","$@")
	@$(WINDRES) $< -O coff -o $@


## Remove generated files
clean:
	@$(call rich_echo,"RM","$(O)/*.o")
	@rm -f $(OBJS) $(ASSETO)

## Remove all built files, including the output
fclean: clean
	@$(call rich_echo,"RM","$(OUTPUT)")
	@rm -f $(OUTPUT)

.PHONY: all re clean fclean


include lib.mk
