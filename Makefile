CC=gcc
CFLAGS=-Wall -Wextra -g3 -fsanitize=undefined -fsanitize-undefined-trap-on-error -I./src
LFLAGS=
SRCS=$(wildcard src/*.c) $(wildcard src/os/*.c) $(wildcard src/ds/*.c)
TESTS := $(wildcard tests/*.c)
TESTBINS := $(TESTS:tests/%.c=tests/build/%)

all: main

main: $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $@ $(LFLAGS) 

tests: tests/build $(TESTBINS)
	for test in $(TESTBINS) ; do ./$$test ; done

tests/build:
	mkdir -p tests/build

tests/build/%: tests/%.c
	$(CC) $(CFLAGS) $(SRCS) -o $@ $< -lcriterion


clean:
	rm main
