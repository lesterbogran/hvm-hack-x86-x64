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
    cpp -P $example.hack > $example.hack.pp
    (set -x; ./hackc $example.hack.pp $example.har)
    rm -r $example.hack.pp
done
