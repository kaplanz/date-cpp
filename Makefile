# -- Directories --
# Root directory
ROOT ?= .

# Input directories
INCLUDE ?= $(ROOT)/include
SRC ?= $(ROOT)/src

# Build directories
BUILD ?= $(ROOT)/build
OBJ ?= $(BUILD)/obj


# -- Files --
# Prerequisites
SRCS := $(wildcard $(SRC)/*.cpp)
OBJS := $(SRCS:$(SRC)/%.cpp=$(OBJ)/%.o)
INCLUDES := $(addprefix -I,$(INCLUDE))

# Targets
TARGET ?= $(BUILD)/$(shell basename "$(CURDIR)")


# -- Commands --
# Shell
MKDIR = mkdir -p
RM = rm -rfv

# Compiler
CXX = c++
CXXFLAGS = -Wall -g -std=c++17 $(INCLUDES)


# -- Recipies --
.PHONY: all
all: $(TARGET)

# Build target executable
$(TARGET): $(OBJS)
	$(CXX) -o $@ $^

$(OBJ)/%.o: $(SRC)/%.cpp
	@$(MKDIR) $(OBJ)
	$(CXX) $(CXXFLAGS) -c $< -o $@


# Run target executable
.PHONY: run
run: $(TARGET)
	@$(TARGET)


# Clean project directory
.PHONY: clean
clean:
	@$(RM) $(BUILD)
