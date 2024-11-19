#! /bin/bash

set +x

find . -type f -name "CMakeCache.txt" -exec rm {} \;
find . -type f -name "cmake_install.cmake" -exec rm {} \;
find . -type d -name "CMakeFiles" -exec rm -r {} \;

find . -type f -name "*.hex" -exec rm {} \;
find . -type f -name "*.elf" -exec rm {} \;

find . -type f -name "compile_commands.json" -exec rm {} \;
find . -type f -name "*.dccache" -exec rm {} \;
find . -type f -name "*.clangd" -exec rm {} \;

set -x