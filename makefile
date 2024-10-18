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

CXX    ?= g++
STDCPP ?= c++17

# Defining macros inside code at compile time. This can be used to enable or disable
# certain features on code or affect the projects compilation.
FLAGS     ?=
CXXFLAGS  ?= -std=$(STDCPP) -I$(DSTDIR) -I$(INCDIR) $(FLAGS)
LINKFLAGS ?=

SRCFILES := $(shell find $(SRCDIR) -name '*.h')                                 \
            $(shell find $(SRCDIR) -name '*.hpp')

EXAMPLES := $(shell find $(EXPDIR) -name '*.cpp')
EXMPBINS = $(EXAMPLES:$(EXPDIR)/%.cpp=$(BINDIR)/$(EXPDIR)/%)
EXMPOBJS = $(EXAMPLES:$(EXPDIR)/%.cpp=$(OBJDIR)/$(EXPDIR)/%.o)

TSTFILES := $(shell find $(TSTDIR) -name '*.cpp')
TESTOBJS = $(TSTFILES:$(TSTDIR)/%.cpp=$(OBJDIR)/$(TSTDIR)/%.o)

# The operational system check. At least for now, we assume that we are always running
# on a Linux machine. Therefore, a disclaimer must be shown if this is not true.
SYSTEMOS := $(shell uname)
SYSTEMOS := $(patsubst MINGW%,Windows,$(SYSTEMOS))
SYSTEMOS := $(patsubst MSYS%,Msys,$(SYSTEMOS))
SYSTEMOS := $(patsubst CYGWIN%,Msys,$(SYSTEMOS))

ifneq ($(SYSTEMOS), Linux)
  $(info Warning: This makefile assumes OS to be Linux.)
endif

# If running an installation target, a prefix variable is used to determine where
# the files must be copied to. In this context, a default value must be provided.
ifeq ($(PREFIX),)
	PREFIX := /usr/local
endif

all:      examples tests
examples: build-examples
tests:    build-tests

prepare-examples:
	@mkdir -p $(sort $(dir $(EXMPBINS)))
	@mkdir -p $(sort $(dir $(EXMPOBJS)))

build-examples: override FLAGS := -DTESTING -g -O0 $(FLAGS)
build-examples: prepare-examples $(EXMPBINS)

prepare-tests:
	@mkdir -p $(BINDIR)/$(TSTDIR)
	@mkdir -p $(sort $(dir $(TESTOBJS)))

build-tests: override FLAGS := -DTESTING -g -O0 $(FLAGS)
build-tests: prepare-tests $(BINDIR)/$(TSTDIR)/runtest

run-tests: build-tests
	$(BINDIR)/$(TSTDIR)/runtest

prepare-distribute:
	@mkdir -p $(DSTDIR)

export DISTRIBUTE_DESTINATION ?= $(shell realpath $(DSTDIR))

SUPERTUPLE_DIST_CONFIG ?= .packconfig
SUPERTUPLE_DIST_TARGET ?= $(DISTRIBUTE_DESTINATION)/$(NAME).h

distribute: prepare-distribute $(SUPERTUPLE_DIST_TARGET)

clean-distribute:
	@rm -rf $(DSTDIR)

export INSTALL_DESTINATION ?= $(PREFIX)/include
INSTALL_TARGETS = $(SRCFILES:$(SRCDIR)/%=$(INSTALL_DESTINATION)/%)

install: $(INSTALL_TARGETS)

$(INSTALL_DESTINATION)/%: $(SRCDIR)/%
	install -m 644 -D -T $< $@

uninstall:
	@rm -f $(INSTALL_TARGETS)

clean: clean-distribute
	@rm -rf $(BINDIR)
	@rm -rf $(OBJDIR)

.PHONY: all clean install uninstall
.PHONY: prepare-distribute distribute clean-distribute
.PHONY: prepare-examples build-examples examples
.PHONY: prepare-tests build-tests tests run-tests

$(SUPERTUPLE_DIST_TARGET): $(SRCFILES)
	@python3 pack.py -c $(SUPERTUPLE_DIST_CONFIG) -o $@

# Creates dependency on header files. This is valuable so that whenever a header
# file is changed, all objects depending on it will be forced to recompile.
ifneq ($(wildcard $(OBJDIR)/.),)
-include $(shell find $(OBJDIR) -name '*.d')
endif

$(BINDIR)/%: $(OBJDIR)/%.o
	$(CXX) $(LINKFLAGS) $< -o $@

$(BINDIR)/$(TSTDIR)/runtest: $(TESTOBJS)
	$(CXX) $(LINKFLAGS) $^ -o $@

$(OBJDIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -I$(TSTDIR) -MMD -c $< -o $@

.PRECIOUS: $(OBJDIR)/%.o
