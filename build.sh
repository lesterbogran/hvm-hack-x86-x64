#!/usr/bin/env sh

set -e

CC="${CC:-cc}"
CFLAGS='-Wall -Wextra -Wswitch-enum -Wmissing-prototypes -pedantic -std=c11'
LIBS=''

(set -x ;\
    $CC $CFLAGS -o hackc  ./src/hackc.c  $LIBS ;\
    $CC $CFLAGS -o hack   ./src/hack.c   $LIBS ;\
    $CC $CFLAGS -o dehack ./src/dehack.c $LIBS)

for example in `find examples/ -name *.hack ! -name *.h.hack | sed "s/.hack//"`; do
    (set -x; ./hackc $example.hack $example.har)
done
