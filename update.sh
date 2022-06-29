#!/bin/bash
cd "$(dirname "$0")"
cd ../addons/godot-rgmap/docs
doxygen doxygen.conf
cd ../../../gh-pages
git add .
git commit -am "Update documentation"
git push origin gh-pages