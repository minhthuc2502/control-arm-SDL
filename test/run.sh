#!/bin/bash -eu
if [[ $1 == "all" ]]; then 
    if [ -d "./bin" ]
    then
        :
    else
        mkdir bin
    fi
    cd bin
    cmake ..
    make
    cd -
fi

if [[ $1 == "clean" ]]; then
    rm -rf bin/*
fi
