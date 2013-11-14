#!/bin/sh

if [[ $# -gt 1 ]]; then
    export FQP_ARGS="-ip -e -a -q $@"
else
    export FQP_ARGS="-ip -e -a -q -fol:AssetsWiki s10 n20 w2000"
fi

make -j`sysctl -n hw.ncpu` -e -f quality.mk all

echo "Ding! Finished running all tests!"
