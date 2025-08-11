# Building texinfo216 makeinfo with SAS/C

This document describes how to build the `makeinfo` command from the texinfo216 project using SAS/C on Amiga OS.

## Prerequisites

- Amiga OS 3.x or compatible
- SAS/C compiler (sc) and linker (slink)
- SMake build system

## Project Structure

The makeinfo command consists of these source files:
- `C/makeinfo.c` - Main program source (173KB)
- `C/getopt.c` - Command-line option parsing
- `C/getopt1.c` - Extended option parsing
- `C/getopt.h` - Header file for getopt functions

## Build Instructions

### 1. Using SMake (Recommended)

```bash
# Build the makeinfo executable
smake all

# Clean build artifacts
smake clean

# Install to C: directory
smake install

# Show available targets
smake help
```

### 2. Using the Build Script

```bash
# Make the script executable
chmod +x build.sh

# Run the build script
./build.sh
```

### 3. Manual Build

```bash
# Compile source files
sc STRIPDEBUG NODEBUG BATCH IDIR=include: IDIR=C: IDIR=. C/makeinfo.c
sc STRIPDEBUG NODEBUG BATCH IDIR=include: IDIR=C: IDIR=. C/getopt.c
sc STRIPDEBUG NODEBUG BATCH IDIR=include: IDIR=C: IDIR=. C/getopt1.c

# Link the executable
slink STRIPDEBUG NODEBUG BATCH FROM makeinfo.o getopt.o getopt1.o TO makeinfo LIB lib:sc.lib lib:small.lib
```

## Configuration

The build system uses these SAS/C options (defined in `SCOPTIONS`):
- `DATA=NEAR` - Data segment in near memory
- `CODE=NEAR` - Code segment in near memory
- `PARAMETERS=REGISTERS` - Pass parameters in registers
- `NOSTACKCHECK` - Disable stack checking
- `OPTIMIZE` - Enable optimization
- `UTILITYLIBRARY` - Link with utility.library

## What is makeinfo?

The `makeinfo` command converts Texinfo format files (`.texi`) into Info files (`.info`) that can be read by the Amiga Info browser. Texinfo is a documentation format that allows you to write documentation once and generate both online help and printed manuals.

## Usage

After building, you can use makeinfo like this:

```bash
# Convert a .texi file to .info
makeinfo input.texi -o output.info

# Show help
makeinfo --help
```

## Troubleshooting

- **Compiler not found**: Ensure SAS/C is installed and `sc` is in your PATH
- **Linker errors**: Check that `lib:sc.lib` and `lib:small.lib` exist
- **Include path issues**: Verify that the include directories exist and contain required headers

## Dependencies

The makeinfo command has minimal dependencies:
- Standard C library functions (stdio, string, ctype, etc.)
- System calls for file operations
- No external libraries beyond the standard SAS/C libraries
