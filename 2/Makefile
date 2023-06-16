FLAGS = -lm -Wall -g

.PHONY: all clear run

all: build_main clear

clear:
	rm -rf build/*

run:
	bin/main

check:
	gcc -o /dev/null $(FLAGS) src/{main.c,math.c,stack.c}

build_main: build/stack.o build/math.o bin/ build/ src/main.c
	$(CC) -o bin/main $(FLAGS) src/main.c build/*

build/math.o: src/math.h src/math.c
	$(CC) -o build/math.o -c $(FLAGS) src/math.c

build/stack.o: src/stack.h src/stack.c
	$(CC) -g -o build/stack.o -c src/stack.c

build/:
	if test -d build; then mkdir build; fi

bin/:
	if test -d bin; then mkdir bin; fi
