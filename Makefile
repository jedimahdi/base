CC=gcc
CFLAGS=-Wall -Wextra -I./include
LFLAGS=-lm
SRCS=$(wildcard src/*.c)
TESTS := $(wildcard tests/*.c)
TESTBINS := $(TESTS:tests/%.c=tests/build/%)

all: main

main: $(SRCS) main.c
	$(CC) $(CFLAGS) main.c $(SRCS) -o $@ $(LFLAGS) 

lib: $(SRCS)
	$(CC) $(CFLAGS) -fPIC -shared $(SRCS) -o lib/libbase.so $(LFLAGS)

tests: tests/build $(TESTBINS)
	for test in $(TESTBINS) ; do ./$$test ; done

tests/build:
	mkdir -p tests/build

tests/build/%: tests/%.c
	$(CC) $(CFLAGS) $(SRCS) -o $@ $< -lcriterion

clean:
	rm main
