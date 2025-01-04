# SuperTuple: A powerful and light-weight C++ tuple implementation.
# @file Makefile for compiling, installing and automatically testing.
# @author Rodrigo Siqueira <rodriados@gmail.com>
# @copyright 2024-present Rodrigo Siqueira
NAME = supertuple

INCDIR = src
SRCDIR = src
EXPDIR = examples
TSTDIR = test

DSTDIR ?= dist
OBJDIR ?= obj
BINDIR ?= bin

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

all: distribute

prepare-distribute:
	@mkdir -p $(DSTDIR)

export DISTRIBUTE_DESTINATION ?= $(shell realpath $(DSTDIR))

SUPERTUPLE_DIST_CONFIG ?= .packconfig
SUPERTUPLE_DIST_TARGET ?= $(DISTRIBUTE_DESTINATION)/$(NAME).h

distribute: prepare-distribute $(SUPERTUPLE_DIST_TARGET)

clean: clean-distribute

clean-distribute:
	@rm -rf $(DSTDIR)

.PHONY: all clean
.PHONY: prepare-distribute distribute clean-distribute

$(SUPERTUPLE_DIST_TARGET): $(SRCFILES)
	@python3 pack.py -c $(SUPERTUPLE_DIST_CONFIG) -o $@
