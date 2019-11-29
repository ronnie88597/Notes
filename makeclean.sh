#!/bin/bash
HOME_DIR=`pwd`
for d in `find . -name cmake-build-debug`;
do
    cd ${HOME_DIR}/$d
    make clean
done
