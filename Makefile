# Makefile for tobecontinued
BACKEND := x11
         # one of x11, win32, quartz

CFLAGS  := $(shell pkg-config --cflags sdl2) -DBACKEND=$(BACKEND)

LDFLAGS := -fPIC
LDLIBS  := $(shell pkg-config --libs sdl2) -lm

ifeq ($(BACKEND),x11)
  LDLIBS += $(shell pkg-config --libs x11)
else ifeq ($(BACKEND),quartz)
  CFLAGS += -iframework CoreGraphics -iframework CoreFoundation
  LDLIBS += -framework CoreGraphics -framework CoreFoundation
endif

O       := .
OUTPUT  := $(O)/tobecont
SOURCES  = src/main.c \
		   src/$(BACKEND)/screenshot.c
ASSETS   = assets/arr.bmp \
           assets/tbc.wav

OBJS     = $(patsubst %.c,$(O)/%.c.o,$(SOURCES))
ASSETO   = $(patsubst %,$(O)/%.raw.o,$(ASSETS))

ifeq ($(BACKEND),win32)
  OBJS += $(O)/assets/tobecont.exe.res
endif

## Build tobecont binary
all: $(OUTPUT)

## Clean up and rebuild
re:: fclean
re:: all

$(OUTPUT): $(ASSETO) $(OBJS)
	@mkdir -p $(@D)
	@$(call rich_echo,"CCLD","$(OUTPUT)")
	@$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

$(O)/%.c.o: %.c
	@mkdir -p $(@D)
	@$(call rich_echo,"CC","$@")
	@$(CC) $(CFLAGS) -c $< -o $@

$(O)/%.raw.o: %
	@mkdir -p $(@D)
ifeq ($(findstring GNU ld, $(shell $(LD) --version)), GNU ld)
	@$(call rich_echo,"LD","$@")
	@$(LD) -r -b binary $< -o $@
else
	@$(call rich_echo,"OBJCOPY","$@")
	@$(eval FILESYM = $(subst /,_,$(subst .,_,$<)))
	@echo -e '.data\n.globl __binary_$(FILESYM)_start\n.globl __binary_$(FILESYM)_end\n__binary_$(FILESYM)_start:\n.incbin "$^"\n__binary_$(FILESYM)_end:' | $(AS) -o $@
endif

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
