INCLUDE = include
DEPS = protocol.h

MODULES = protocol.o

TESTMODULES = tests/test_packing.o

CC=gcc
CFLAGS=-Wall -std=c99 -I$(INCLUDE)
LDFLAGS=-lhidapi


%.o: %.c $(DEPS)
	@$(CC) -c -o $@ $< $(CFLAGS)

tests/%.o: tests/%.c tests/cutest.h
	@$(CC) -c -o $@ $< $(CFLAGS)

all: clean tests mstest

tests: $(TESTMODULES) $(MODULES)
	@$(CC) -o tests/runtests $^ $(CFLAGS)
	tests/runtests

mstest: mstest.o $(MODULES)
	@$(CC) -o mstest $^ $(LDFLAGS) $(CFLAGS)

clean:
	@rm -f *.o
	@rm -f tests/*.o



