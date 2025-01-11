# SuperTuple: A powerful and light-weight C++ tuple implementation.
# @file Makefile for bundling header files into a single one.
# @author Rodrigo Siqueira <rodriados@gmail.com>
# @copyright 2024-present Rodrigo Siqueira
NAME = supertuple

INCDIR = src
SRCDIR = src
TSTDIR = test

BINDIR ?= build

SRCFILES := $(shell find $(SRCDIR) -name '*.h')                                \
            $(shell find $(SRCDIR) -name '*.hpp')

# The operational system check. At least for now, we assume that we are always running
# on a Linux machine. Therefore, a disclaimer must be shown if this is not true.
SYSTEMOS := $(shell uname)
SYSTEMOS := $(patsubst MINGW%,Windows,$(SYSTEMOS))
SYSTEMOS := $(patsubst MSYS%,Msys,$(SYSTEMOS))
SYSTEMOS := $(patsubst CYGWIN%,Msys,$(SYSTEMOS))

ifneq ($(SYSTEMOS), Linux)
  $(info Warning: This makefile assumes OS to be Linux.)
endif

all: pack

prepare-pack:
	@mkdir -p $(BINDIR)

export PACK_DESTINATION ?= $(shell realpath $(BINDIR))

SUPERTUPLE_PACK_CONFIG ?= .packconfig
SUPERTUPLE_PACK_TARGET ?= $(PACK_DESTINATION)/$(NAME).h

pack: prepare-pack $(SUPERTUPLE_PACK_TARGET)

clean: clean-pack

clean-pack:
	@rm $(SUPERTUPLE_PACK_TARGET)

.PHONY: all clean
.PHONY: prepare-pack pack clean-pack

$(SUPERTUPLE_PACK_TARGET): $(SRCFILES)
	@python3 pack.py -c $(SUPERTUPLE_PACK_CONFIG) -o $@
