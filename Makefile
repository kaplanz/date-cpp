# Root directory
ROOT ?= .
# Input directories
INCLUDE ?= $(ROOT)/include
SRC ?= $(ROOT)/src
# Build directories
BUILD ?= $(ROOT)/build
OBJ ?= $(BUILD)/obj

# Prerequisites
SRCS := $(wildcard $(SRC)/*.cpp)
OBJS := $(SRCS:$(SRC)/%.cpp=$(OBJ)/%.o)
INCLUDES := $(addprefix -I,$(INCLUDE))
# Targets
TARGET ?= $(BUILD)/$(shell basename "$(CURDIR)")

# Commands
MKDIR = mkdir -p
RM = rm -rfv
# Compiler
CXX = c++
CXXFLAGS = -Wall -g -std=c++17 $(INCLUDES)

# Build target executable
.PHONY: all
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $@ $^

$(OBJ)/%.o: $(SRC)/%.cpp
	@$(MKDIR) $(OBJ)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run target executable
.PHONY: run
run: $(TARGET)
	@$(TARGET)

# Clean build directory
.PHONY: clean
clean:
	@$(RM) $(BUILD)
