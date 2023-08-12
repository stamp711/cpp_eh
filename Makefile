CC = gcc
CXX = g++


all: app

main.o: main.c
	${CC} main.c -c -o main.o

throw.o: throw.cpp
	${CXX} throw.cpp -c -o throw.o

app: main.o throw.o
	${CC} main.o throw.o -O0 -o app

.PHONY: clean run
clean:
	rm -f main.o throw.o mycppabi.o app

run: app
	./app