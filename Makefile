##
# hvm
#
# @file
# @version 0.1

CFLAGS=-Wall -Wextra -Wswitch-enum -Wmissing-prototypes -pedantic -std=c11
LIBS=

EXAMPLES=./examples/fib.har ./examples/123f.har ./examples/123i.har ./examples/e.har ./examples/pi.har ./examples/lerp.har

.PHONY: all
all: hackc hack dehack

hackc: ./src/hackc.c ./src/hvm.h
	$(CC) $(CFLAGS) -o hackc ./src/hackc.c $(LIBS)

hack: ./src/hack.c ./src/hvm.h
	$(CC) $(CFLAGS) -o hack ./src/hack.c $(LIBS)

dehack: ./src/dehack.c ./src/hvm.h
	$(CC) $(CFLAGS) -o dehack ./src/dehack.c $(LIBS)

.PHONY: examples
examples: $(EXAMPLES)

%.har: %.hack hackc
	./hackc $< $@

# end
