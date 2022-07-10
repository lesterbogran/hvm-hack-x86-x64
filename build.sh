#!/usr/bin/env sh

set -e

CC=${CC:-cc}
CFLAGS='-Wall -Wextra -Wswitch-enum -Wmissing-prototypes -Wconversion -pedantic -fno-strict-aliasing -ggdb -std=c11'
LIBS=

(set -x ;\
    $CC $CFLAGS -o hackc     ./src/hackc.c     $LIBS ;\
    $CC $CFLAGS -o hack      ./src/hack.c      $LIBS ;\
    $CC $CFLAGS -o hdb       ./src/hdb.c       $LIBS ;\
    $CC $CFLAGS -o hack2nasm ./src/hack2nasm.c $LIBS ;\
    $CC $CFLAGS -o dehack    ./src/dehack.c    $LIBS)

for example in `find examples/ -name *.hack ! -name natives.hack | sed "s/.hack//"`; do
    (set -x; ./hackc -d $example.hack $example.har)
done
