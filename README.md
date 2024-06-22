<br>

# Unix C Project Template

<br>

## Overview

This is a C project template for Unix-based systems. It provides a basic structure and configuration for building C projects using a Makefile.

<br>

## Project Structure

The project has the following directory structure:

- `include/`: contains header files (`.h`) that declare functions and define constants.
  - `interface.h`: single header file for the project.
- `src/`: contains source files (`.c`) that implement the functionality of the project.
  - `main.c`: the main source file of the project, which contains the `main()` function.
  - `array.c`: functions that use the dynamic string data type.
  - `list.c`: functions that use the dynamic list data type.
  - `files.c`: functions handling file I/O.
  - `terminal.c`: functions handling terminal I/O.
  - `misc.c`: miscellaneous helper functions. 
- `Makefile`: Defines the build rules and configuration for the project.

<br>

## Build System

The project uses a Makefile to automate the build process. The Makefile defines the following variables and rules:

- `CXX`: specifies the compiler to use (default: `gcc`).
- `CXXFLAGS`: specifies the compiler flags, including the include directory and warning options.
- `TARGET`: specifies the name of the target executable.
- `SRC_DIR`: specifies the directory containing the source files.
- `BIN_DIR`: specifies the directory where object files will be generated.
- `INCLUDE_DIR`: specifies the directory containing the header files.
- `SRCS`: lists all the source files in the `SRC_DIR`.
- `OBJS`: lists the corresponding object files for each source file.

The Makefile provides the following rules:

- `$(TARGET)`: builds the target executable by linking the object files.
- `$(BIN_DIR)/%.o`: compiles the source files into object files.
- `clean`: removes the object files and the target executable.

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