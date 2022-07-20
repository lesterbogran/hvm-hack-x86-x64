#!/usr/bin/env sh

set -e

CC=${CC:-cc}
CFLAGS='-Wall -Wextra -Wswitch-enum -Wmissing-prototypes -Wconversion -pedantic -fno-strict-aliasing -ggdb -std=c11'
LIBS=

mkdir -p build/bin
mkdir -p build/examples

(set -x ;\
 $CC $CFLAGS -o build/bin/hackc     ./src/hackc.c     $LIBS ;\
 $CC $CFLAGS -o build/bin/hack      ./src/hack.c      $LIBS ;\
 $CC $CFLAGS -o build/bin/hdb       ./src/hdb.c       $LIBS ;\
 $CC $CFLAGS -o build/bin/hack2nasm ./src/hack2nasm.c $LIBS ;\
 $CC $CFLAGS -o build/bin/dehack    ./src/dehack.c    $LIBS
)

for example in `find examples/ -name *.hack ! -name natives.hack | sed "s/.hack//"`; do
    (set -x; ./build/bin/hackc -d $example.hack build/$example.har)
done
