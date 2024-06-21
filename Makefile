# Compiler to use
CXX = gcc

# Compiler flags
CXXFLAGS = -Iinclude -Wall -Wextra

# Target executable name
TARGET = main

# Directories
SRC_DIR = src
BIN_DIR = obj
INCLUDE_DIR = include

# Source and object files
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/%.o, $(SRCS))

# Rule for building the target
$(TARGET): $(OBJS)
	$(CXX) $^ $(CXXFLAGS) -lm -o $@

# Rule for generating object files
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(BIN_DIR)/*.o $(TARGET)