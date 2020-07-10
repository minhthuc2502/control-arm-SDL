#!/bin/bash -eu
usage(){
    echo "Usage: $0 <source path>"
}
# Test path
[ $# -lt 1 ] && echo ["ERROR: too few arguments  to script $0"] && usage && exit 1
[ ! -d $1 ] && echo "ERROR: source path given is invalid!" && exit 1
src_dir=$(realpath "$1")
# Test build path
if [ ! -d "${src_dir}/out" ]; then
    mkdir ${src_dir}/out
fi
out_dir="${src_dir}/out"
# build project
echo "Building source code ..."
cd ${out_dir}
cmake ${src_dir} && make -j4