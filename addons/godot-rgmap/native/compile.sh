#!/bin/sh
cd "$(dirname "$0")"
if [[ "$1" == "--debug" ]]; then
    scons platform=linux target=debug -j8
else
    echo -e "Compiling for Linux: \n"
    scons platform=linux target=release -j8
    echo -e "\nCompiling for Windows: \n"
    scons platform=windows target=release use_mingw=yes -j8
    echo -e "\nCompiling for OSX: \n"
    scons platform=osx target=release use_llvm=yes -j8
fi