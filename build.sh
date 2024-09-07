#!/bin/bash

set -xe

CFLAGS="-Wall -Werror -Wextra -pedantic -std=c17 -g"

mkdir -p build

gcc -o ./build/conway main.c conway.c ${CFLAGS}
