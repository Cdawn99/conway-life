#!/bin/bash

set -xe

gcc -Wall -Werror -Wextra main.c conway.c -o build/conway
