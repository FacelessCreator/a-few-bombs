.PHONY: clear all test test-forkbomb

all:
	echo "Nothing at the moment"

clear:
	rm -r build log

test: test-forkbomb

test-forkbomb: build/test-forkbomb build/forkbomb
	build/test-forkbomb

test-membomb: build/test-membomb build/membomb
	build/test-membomb

build:
	mkdir -p build

build/forktest: build src/forktest.cpp
	g++ src/forktest.cpp -o build/forktest

build/forkbomb: build src/forkbomb.cpp
	g++ src/forkbomb.cpp -o build/forkbomb

build/test-forkbomb: build src/test-forkbomb.cpp src/etc.hpp
	g++ src/test-forkbomb.cpp -o build/test-forkbomb

build/membomb: build src/membomb.cpp
	g++ src/membomb.cpp -o build/membomb

build/test-membomb: build src/test-membomb.cpp src/etc.hpp
	g++ src/test-membomb.cpp -o build/test-membomb
