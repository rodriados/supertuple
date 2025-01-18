# SuperTuple: A powerful and light-weight C++ tuple implementation.
# @file Makefile for building examples.
# @author Rodrigo Siqueira <rodriados@gmail.com>
# @copyright 2025-present Rodrigo Siqueira
NAME = supertuple-examples

INCDIR = ../src
BINDIR ?= build

CPPCPL ?= g++
STDCPP ?= c++17

# Defining macros inside code at compile time. This can be used to enable or disable
# certain features on code or affect the projects compilation.
FLAGS ?= -Wall
LINKFLAGS ?= -lCatch2Main -lCatch2
CPPFLAGS  ?= -std=$(STDCPP) -I$(INCDIR) $(FLAGS)

SRCFILES := $(shell find $(SRCDIR) -name '*.cpp')
EXAMPLES = $(SRCFILES:./%.cpp=$(BINDIR)/%)

# The operational system check. At least for now, we assume that we are always running
# on a Linux machine. Therefore, a disclaimer must be shown if this is not true.
SYSTEMOS := $(shell uname)
SYSTEMOS := $(patsubst MINGW%,Windows,$(SYSTEMOS))
SYSTEMOS := $(patsubst MSYS%,Msys,$(SYSTEMOS))
SYSTEMOS := $(patsubst CYGWIN%,Msys,$(SYSTEMOS))

ifneq ($(SYSTEMOS), Linux)
  $(info Warning: This makefile assumes OS to be Linux.)
endif

all: build

prepare-build:
	@mkdir -p $(BINDIR)

build: prepare-build $(EXAMPLES)

clean: clean-build

clean-build:
	@rm -f $(EXAMPLES)

.PHONY: all clean
.PHONY: prepare-build build clean-build

# Creates dependency on header files. This is valuable so that whenever a header
# file is changed, all objects depending on it will be forced to recompile.
ifneq ($(wildcard $(BINDIR)/.),)
-include $(shell find $(BINDIR) -name '*.d')
endif

$(BINDIR)/%: %.cpp
	$(CPPCPL) $(CPPFLAGS) $^ -o $@ $(LINKFLAGS)
