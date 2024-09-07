#!/bin/bash

set -xe

CFLAGS="-Wall -Werror -Wextra -pedantic -std=c17 -g"
INCLUDES="-I./raylib-5.0_linux_amd64/include"
LIBS="-L./raylib-5.0_linux_amd64/lib -lraylib -lm"

mkdir -p build

gcc -o ./build/console_conway console_main.c conway.c ${CFLAGS}
gcc -o ./build/gui_conway gui_main.c conway.c ${CFLAGS} ${INCLUDES} ${LIBS}
