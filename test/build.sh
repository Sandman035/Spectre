#!/bin/bash
# Build script for testbed
set echo on

mkdir -p ../bin

# Get a list of all the .c files.
cFilenames=$(find . -type f -name "*.cpp")

# echo "Files:" $cFilenames

assembly="testbed"
compilerFlags="-g -fdeclspec -fPIC" 
includeFlags="-Isrc -I../spectre/src/"
linkerFlags="-L../bin/ -lspectre -Wl,-rpath,. -lstdc++"
defines="-D_DEBUG -DIMPORT"

echo "Building $assembly..."
echo clang $cFilenames $compilerFlags -o ../bin/$assembly $defines $includeFlags $linkerFlags
clang $cFilenames $compilerFlags -o ../bin/$assembly $defines $includeFlags $linkerFlags
