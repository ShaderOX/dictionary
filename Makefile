CC=g++
CFLAGS=-Wall -g -std=c++17 -O0 -Wextra -Wpedantic

all: main 

%: src/%.cpp src/*.h
	$(CC) $(CFLAGS) -o dist/$@ $<


clean: 
	rm -f dist/*
