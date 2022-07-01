##
# hvm
#
# @file
# @version 0.1

CFLAGS=-Wall -Wextra -Wswitch-enum -Wmissing-prototypes -pedantic -std=c11
LIBS=
RM?=rm -f

EXAMPLES!=find examples/ -name \*.hack | sed "s/\.hack/\.har/"
BINARIES=hackc \
		 hack  \
		 dehack

.SUFFIXES: .hack .har

.hack.har:
	./hackc $< $@

.PHONY: all
all: ${BINARIES}

hackc: ./src/hackc.c ./src/hvm.h
	$(CC) $(CFLAGS) -o hackc ./src/hackc.c $(LIBS)

hack: ./src/hack.c ./src/hvm.h
	$(CC) $(CFLAGS) -o hack ./src/hack.c $(LIBS)

dehack: ./src/dehack.c ./src/hvm.h
	$(CC) $(CFLAGS) -o dehack ./src/dehack.c $(LIBS)

.PHONY: examples
examples: hackc ${EXAMPLES}

.PHONY: clean
clean:
	${RM} ${EXAMPLES}
	${RM} ${BINARIES}

# end
