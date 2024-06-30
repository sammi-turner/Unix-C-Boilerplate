<br>

# Unix C Boilerplate

<br>

## Overview

This repo provides a basic structure and configuration for building C projects using a Makefile. It also contains a codebase of potentially useful library code.

<br>

## Project Structure

The project has the following directory structure:

- `include/`: contains header files (`.h`) that declare functions and define constants.
  - `interface.h`: single header file for the project.
- `src/`: contains source files (`.c`) that implement the functionality of the project.
  - `main.c`: the main source file of the project, which contains the `main()` function.
  - `dynamic.c`: functions that use the dynamic string type.
  - `files.c`: functions handling file I/O.
  - `terminal.c`: functions handling terminal I/O.
  - `strings.c`: string helper functions.
  - `misc.c`: miscellaneous helper functions. 
- `Makefile`: Defines the build rules and configuration for the project.

<br>

## Makefile

This project uses a Makefile to automate the build process. Here is a breakdown of its contents.

### Compiler and Flags

- `CC = gcc`: Uses GCC as the compiler.
- `CFLAGS = -Iinclude -Wall -Wextra -std=c11`: Compiler flags:
  - `-Iinclude`: Adds the `include` directory to the include path.
  - `-Wall -Wextra`: Enables comprehensive warning messages.
  - `-std=c11`: Uses the C11 standard.

### Directories

- `SRC_DIR = src`: Source files directory.
- `BIN_DIR = obj`: Object files directory.
- `INCLUDE_DIR = include`: Header files directory.

### Files

- `SRCS = $(wildcard $(SRC_DIR)/*.c)`: Finds all .c files in the src directory.
- `OBJS = $(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/%.o, $(SRCS))`: Generates object file names from source files.

### OS Detection

- Detects the operating system using `uname -s`.
- For macOS (Darwin), adds `-liconv` to the linker flags.

### Build Rules

1. Main target rule: Compiles object files into the final executable.
2. Object file rule: Compiles .c files into .o files.

### Usage

- Run `make` to build the project.
- Run `make clean` to remove compiled files.

Note: This Makefile assumes a specific project structure with src, obj, and include directories.

<br>

## Building the Project

To build the project, follow these steps:

1. Navigate to the project directory in the terminal.
2. Run the command `make` to build the project.
3. The compiled executable will be generated with the name specified in the `TARGET` variable.

To clean the project and remove the generated files, run the command `make clean`.

<br>

## Running the Project

After building the project, you can run the executable by executing the following command in the terminal:

​```
./main
​```

<br>
