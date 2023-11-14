#!/bin/bash

set -xe

mkdir -p build

gcc -Wall -Werror -Wextra main.c conway.c -o build/conway
