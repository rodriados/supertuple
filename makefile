# SuperTuple: A powerful and light-weight C++ tuple implementation.
# @file Makefile for compiling, installing and automatically testing.
# @author Rodrigo Siqueira <rodriados@gmail.com>
# @copyright 2024-present Rodrigo Siqueira
NAME = supertuple

INCDIR = src
SRCDIR = src
EXPDIR = examples
DSTDIR = dist
TSTDIR = test

OBJDIR = obj
BINDIR = bin

CXX    ?= g++
STDCPP ?= c++17

# Defining macros inside code at compile time. This can be used to enable or disable
# certain features on code or affect the projects compilation.
FLAGS     ?=
LINKFLAGS ?=
CXXFLAGS  ?= -std=$(STDCPP) -I$(INCDIR) $(FLAGS)

SRCFILES := $(shell find $(SRCDIR) -name '*.h')                                 \
            $(shell find $(SRCDIR) -name '*.hpp')
EXAMPLES := $(shell find $(EXPDIR) -name '*.cpp')
EXMPBINS = $(EXAMPLES:$(EXPDIR)/%.cpp=$(BINDIR)/$(EXPDIR)/%)
EXMPOBJS = $(EXAMPLES:$(EXPDIR)/%.cpp=$(OBJDIR)/$(EXPDIR)/%)

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

all: examples

examples: build-examples

prepare-examples:
	@mkdir -p $(sort $(dir $(EXMPBINS)))
	@mkdir -p $(sort $(dir $(EXMPOBJS)))

build-examples: override FLAGS := -DTESTING $(FLAGS)
build-examples: prepare-examples $(EXMPBINS)

clean-examples:
	@rm -rf $(BINDIR)/$(EXPDIR)
	@rm -rf $(OBJDIR)/$(EXPDIR)

prepare-distribute:
	@mkdir -p $(DSTDIR)

distribute: DISTRIBUTE_CONFIG ?= .packconfig
distribute: DISTRIBUTE_TARGET ?= $(DSTDIR)/$(NAME).hpp
distribute: prepare-distribute
	python pack.py -c $(DISTRIBUTE_CONFIG) -o $(DISTRIBUTE_TARGET)

clean-distribute:
	@rm -rf $(DSTDIR)

INSTALL_DESTINATION ?= $(DESTDIR)$(PREFIX)/include
INSTALL_TARGETS = $(SRCFILES:$(SRCDIR)/%=$(INSTALL_DESTINATION)/%)

install: $(INSTALL_TARGETS)

$(INSTALL_DESTINATION)/%: $(SRCDIR)/%
	install -m 644 -D -T $< $@

clean:
	@rm -rf $(BINDIR)
	@rm -rf $(OBJDIR)
	@rm -rf $(DSTDIR)

.PHONY: all clean install examples
.PHONY: prepare-distribute distribute clean-distribute
.PHONY: prepare-examples build-examples clean-examples

# Creates dependency on header files. This is valuable so that whenever a header
# file is changed, all objects depending on it will be forced to recompile.
ifneq ($(wildcard $(OBJDIR)/.),)
-include $(shell find $(OBJDIR) -name '*.d')
endif

$(BINDIR)/%: $(OBJDIR)/%.o
	$(CXX) $(LINKFLAGS) $< -o $@

$(OBJDIR)/$(EXPDIR)/%.o: $(EXPDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -MMD -c $< -o $@
