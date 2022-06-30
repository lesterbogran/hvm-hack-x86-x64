##
# hvm
#
# @file
# @version 0.1

CFLAGS=-Wall -Wextra -Wswitch-enum -Wmissing-prototypes -pedantic -std=c11
LIBS=

.PHONY: all
all: hackc hack dehack

hackc: ./src/hackc.c ./src/hvm.h
	$(CC) $(CFLAGS) -o hackc ./src/hackc.c $(LIBS)

hack: ./src/hack.c ./src/hvm.h
	$(CC) $(CFLAGS) -o hack ./src/hack.c $(LIBS)

dehack: ./src/dehack.c ./src/hvm.h
	$(CC) $(CFLAGS) -o dehack ./src/dehack.c $(LIBS)


.PHONY: examples
examples: ./examples/fib.har ./examples/123f.har ./examples/123i.har

./examples/fib.har: hackc ./examples/fib.hack
	./hackc ./examples/fib.hack ./examples/fib.har

./examples/123f.har: hackc ./examples/123f.hack
	./hackc ./examples/123f.hack ./examples/123f.har

./examples/123i.har: hackc ./examples/123i.hack
	./hackc ./examples/123i.hack ./examples/123i.har

# end
