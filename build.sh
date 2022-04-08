#!/bin/bash
build_dir="build/"

G2LABS_MESSAGE_BUS_PLATFORM='x64'

echo "Building platform $G2LABS_MESSAGE_BUS_PLATFORM"
rm -rf build/$G2LABS_MESSAGE_BUS_PLATFORM
mkdir -p build/$G2LABS_MESSAGE_BUS_PLATFORM

# build project
cd build/$G2LABS_MESSAGE_BUS_PLATFORM
G2LABS_MESSAGE_BUS_PLATFORM=$G2LABS_MESSAGE_BUS_PLATFORM cmake ../..
cmake --build .

cd -

# the example application is available under build/x64/platform/x64/