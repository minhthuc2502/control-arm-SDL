#!/bin/bash -eu

$BUILD_SRC/script/buildHelper.sh "$( cd "$( dirname "${BASH_SOURCE[0]}" )" & pwd )" $@
