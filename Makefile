#
# MIT License
#
# Copyright (c) 2020 Zakhary Kaplan
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#

# --------------------------------
#            Variables
# --------------------------------

# Root directory
ROOT ?= .
# Input directories
INCLUDE ?= $(ROOT)/include
LIB ?= $(ROOT)/lib
SRC ?= $(ROOT)/src
TEST ?= $(ROOT)/test
# Build directories
BUILD ?= $(ROOT)/build
# Build subdirectories (absolute)
BINLINK := $(BUILD)/../bin
# Build subdirectories (relative)
ARC = $(BUILD)/lib
BIN = $(BUILD)/bin
DEP = $(BUILD)/dep
OBJ = $(BUILD)/obj
# Search directories
INCLUDES := $(addprefix -I,$(INCLUDE))

# Sources
HEADERS := $(shell find -L $(ROOT) -name "*.h")
SOURCES := $(shell find -L $(ROOT) -name "*.c" -o -name "*.cpp")
# Prerequisites
LIBS := $(filter $(LIB)/%,$(SOURCES))
SRCS := $(filter $(SRC)/%,$(SOURCES))
TSTS := $(filter $(TEST)/%,$(SOURCES))
# Intermediate targets
ARCS := $(sort $(patsubst %/,%,$(dir $(LIBS))))
# Targets
ARCHS = $(ARCS:$(LIB)/%=$(ARC)/lib%.a)
BINS = $(filter-out %.c %.cpp,$(SRCS:$(SRC)/%.c=$(BIN)/%) \
                              $(SRCS:$(SRC)/%.cpp=$(BIN)/%))
DEPS = $(OBJS:$(OBJ)/%.o=$(DEP)/%.d)
OBJS = $(filter %.o,$(LIBS:$(LIB)/%.c=$(OBJ)/%.o) \
                    $(LIBS:$(LIB)/%.cpp=$(OBJ)/%.o) \
                    $(SRCS:$(SRC)/%.c=$(OBJ)/%.o) \
                    $(SRCS:$(SRC)/%.cpp=$(OBJ)/%.o))
TESTS = $(filter-out %.c %.cpp,$(TSTS:$(ROOT)/%.c=$(BIN)/%) \
                               $(TSTS:$(ROOT)/%.cpp=$(BIN)/%))

# Commands
CHECK = clang-tidy
FIX = clang-tidy --fix-errors
FMT = clang-format --verbose -i
LN = ln -sf
MKDIR = mkdir -p
RM = rm -rfv
# Compiler
AR = ar
CC = cc
CXX = c++
# Flags
ARFLAGS = crs
CFLAGS ?= -Wall -g -std=c18
CPPFLAGS += $(INCLUDES)
CXXFLAGS ?= -Wall -g -std=c++17
DEPFLAGS = -MM -MF $@ -MT $(OBJ)/$*.o
LDFLAGS ?=
LDLIBS ?=

# Alternate build settings
MODES = DEBUG DEFAULT RELEASE
CONFIG ?= DEFAULT
ifneq ($(filter $(CONFIG),$(MODES)),)
$(CONFIG) = 1
else
$(error unknown build: `$(CONFIG)`)
endif

ifdef DEBUG # debug build
BUILD := $(BUILD)/debug
CPPFLAGS += -O0 -g3 -DDEBUG
else ifdef RELEASE # release build
BUILD := $(BUILD)/release
CPPFLAGS += -O3 -g0 -DNDEBUG
endif


# --------------------------------
#              Rules
# --------------------------------

# Build all executables
.PHONY: all
all: $(BINS)

# Make alternate builds
.PHONY: debug
debug: export DEBUG = 1
debug:
	@$(MAKE) all

.PHONY: release
release: export RELEASE = 1
release:
	@$(MAKE) all

# Link target executables
$(BIN)/%: $(OBJ)/%.o $(ARCHS) | $(BINLINK)/%
	@$(MKDIR) $(@D)
	$(LINK.cc) -o $@ $^ $(LDLIBS)

$(BINLINK)/%: FORCE
	@$(MKDIR) $(@D)
	@$(LN) $(shell realpath -m $(BIN)/$* --relative-to $(@D)) $@

# Run target executables
%: $(BIN)/% FORCE ; @$< $(ARGS)

# Generate dependency files
.PHONY: dep
dep: $(DEPS)

$(DEP)/%.d: %.c
	@$(MKDIR) $(@D)
	$(COMPILE.c) $(DEPFLAGS) $<

$(DEP)/%.d: %.cpp
	@$(MKDIR) $(@D)
	$(COMPILE.cc) $(DEPFLAGS) $<

# Compile object files
.PHONY: obj
obj: $(OBJS)

$(OBJ)/%.o: %.c | $(DEP)/%.d
	@$(MKDIR) $(@D)
	$(COMPILE.c) -o $@ $<

$(OBJ)/%.o: %.cpp | $(DEP)/%.d
	@$(MKDIR) $(@D)
	$(COMPILE.cc) -o $@ $<

# Create library archives
.PHONY: lib
lib: $(ARCHS)

.SECONDEXPANSION:
$(ARC)/lib%.a: $$(filter $(OBJ)/%/$$(PERCENT),$(OBJS)) | $(LIB)/%/*
	@$(MKDIR) $(@D)
	$(AR) $(ARFLAGS) $@ $^

# Create target archive
%: $(ARC)/lib%.a FORCE ;

# Compile tests
.PHONY: test
test: $(TESTS)
	$(foreach TEST,$^,$(TEST))

# Clean build directory
.PHONY: clean
clean:
	@$(RM) $(BINLINK) $(BUILD)

# Check sources
.PHONY: check
check:
	@$(CHECK) $(SOURCES) -- $(INCLUDES)

# Fix sources
.PHONY: fix
fix:
	@$(FIX) $(SOURCES) -- $(INCLUDES)

# Format sources
.PHONY: fmt
fmt:
	@$(FMT) $(HEADERS) $(SOURCES)


# --------------------------------
#              Extras
# --------------------------------

# Search path
vpath %.c $(LIB) $(ROOT) $(SRC)
vpath %.cpp $(LIB) $(ROOT) $(SRC)

# Special variables
PERCENT := %

# Special targets
.PHONY: FORCE
FORCE: # force implicit pattern rules

.PRECIOUS: \
	$(BIN)/% \
	$(BINLINK)/% \
	$(DEP)/%.d \
	$(OBJ)/%.o \

.SUFFIXES: # delete the default suffixes

# Includes
include $(wildcard $(DEPS))
