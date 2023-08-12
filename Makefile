CC = gcc
CXX = g++
CFLAGS = -O0 -g -Wall -Wextra
CXXFLAGS = -std=c++20 -O0 -g -Wall -Wextra

all: app

main.o: main.c
	${CC} ${CFLAGS} main.c -c -o main.o

throw.o: throw.cpp throw.h
	${CXX} ${CXXFLAGS} throw.cpp -c -o throw.o

eh_abi.o: eh_abi.cpp
	${CXX} ${CXXFLAGS} eh_abi.cpp -c -o eh_abi.o

app: main.o throw.o eh_abi.o
	${CC} main.o throw.o eh_abi.o -O0 -o app

.PHONY: clean run
clean:
	rm -f main.o throw.o eh_abi.o app

run: app
	./app