##
# hvm
#
# @file
# @version 0.1

CFLAGS=-Wall -Wextra -Wswitch-enum -std=c11 -pedantic
LIBS=

.PHONY: all
all: hackc hack

hackc: ./src/hackc.c ./src/hvm.c
	$(CC) $(CFLAGS) -o hackc ./src/hackc.c $(LIBS)

hack: ./src/hack.c ./src/hvm.c
	$(CC) $(CFLAGS) -o hack ./src/hack.c $(LIBS)


.PHONY: examples
examples: ./examples/fib.har ./examples/123.har

./examples/fib.har: ./examples/fib.hack
	./hackc ./examples/fib.hack ./examples/fib.har

./examples/123.har: ./examples/123.hack
	./hackc ./examples/123.hack ./examples/123.har

# end
