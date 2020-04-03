#!/bin/bash -eu
if [ -d "./out" ]
then
    :
else
    mkdir out
fi
cd out
cmake ..
make
cd -
