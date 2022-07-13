#!/bin/sh

set -xe

./build.sh

./hack2nasm ./examples/123i.hack > ./examples/123i.asm
nasm -felf64 -g ./examples/123i.asm -o ./examples/123i.o
ld -o ./examples/123i.exe ./examples/123i.o

./hack2nasm ./examples/fib.hack > ./examples/fib.asm
nasm -felf64 -g ./examples/fib.asm -o ./examples/fib.o
ld -o ./examples/fib.exe ./examples/fib.o

# TODO(#37): not all of the examples are translatable with hack2nasm
