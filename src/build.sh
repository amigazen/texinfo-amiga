#!/bin/sh
# Build script for texinfo216 makeinfo command
# For Amiga OS with SAS/C

echo "Building texinfo216 makeinfo command..."
echo "Using SAS/C compiler..."

# Check if SAS/C is available
if ! command -v sc >/dev/null 2>&1; then
    echo "Error: SAS/C compiler (sc) not found in PATH"
    echo "Please ensure SAS/C is installed and in your PATH"
    exit 1
fi

# Clean previous build
echo "Cleaning previous build..."
smake clean

# Build the project
echo "Building makeinfo..."
smake all

# Check if build was successful
if [ -f "makeinfo" ]; then
    echo "Build successful! makeinfo executable created."
    echo "You can now run: smake install"
else
    echo "Build failed! Check for compilation errors."
    exit 1
fi
