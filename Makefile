##
# hvm
#
# @file
# @version 0.1

CFLAGS=-Wall -Wextra -Wswitch-enum -std=c11 -pedantic
LIBS=

.PHONY: all
all: hackc hack

hackc: hackc.c hvm.c
	$(CC) $(CFLAGS) -o hackc hackc.c $(LIBS)

hack: hack.c hvm.c
	$(CC) $(CFLAGS) -o hack hack.c $(LIBS)


.PHONY: examples
examples: ./examples/fib.har ./examples/123.har

./examples/fib.har: ./examples/fib.hack
	./hackc ./examples/fib.hack ./examples/fib.har

./examples/123.har: ./examples/123.hack
	./hackc ./examples/123.hack ./examples/123.har

# end
