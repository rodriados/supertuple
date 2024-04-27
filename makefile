# SuperTuple: A powerful and light-weight C++ tuple implementation.
# @file Makefile for compiling, installing and automatically testing.
# @author Rodrigo Siqueira <rodriados@gmail.com>
# @copyright 2024-present Rodrigo Siqueira
NAME = supertuple

INCDIR = src
SRCDIR = src
EXPDIR = examples
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

EXAMPLES := $(shell find $(EXPDIR) -name '*.cpp')
EXMPBINS = $(EXAMPLES:$(EXPDIR)/%.cpp=$(BINDIR)/$(EXPDIR)/%)
EXMPOBJS = $(EXAMPLES:$(EXPDIR)/%.cpp=$(OBJDIR)/$(EXPDIR)/%)

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

clean:
	@rm -rf $(BINDIR)
	@rm -rf $(OBJDIR)

.PHONY: all clean examples
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
