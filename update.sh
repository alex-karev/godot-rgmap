#!/bin/bash
cd "$(dirname "$0")"
doxygen doxygen.conf
git add .
git commit -am "Update documentation"
git push origin gh-pages