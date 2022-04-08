#!/bin/bash
build_dir="build/"

PLATFORM='x64'

echo "Building platform $PLATFORM"
rm -rf build/$PLATFORM
mkdir -p build/$PLATFORM

# assemble example fibonacci code
python3 assembler/g2labs-virtual-machine-assembler.py assembler/examples/fibonacci.g2 -o platform/x64/virtual_machine_source

# build project
cd build/$PLATFORM
PLATFORM=$PLATFORM cmake ../..
cmake --build .

cd -

# the example application is available under build/x64/platform/x64/