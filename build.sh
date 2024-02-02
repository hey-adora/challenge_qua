#!/usr/bin/env sh
rm -rf ./build
rm -rf ./bin
mkdir -p build
cd build
cmake ..
make
ctest --verbose