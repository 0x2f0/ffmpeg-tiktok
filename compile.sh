#!/usr/bin/env bash

set -e

rm -f ./out/output.mp4 

gcc -Wall \
    -Wextra \
     generate.c -o ./out/editor

./out/editor

ffplay ./out/output.mp4
