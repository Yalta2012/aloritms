CC = g++-13
FLAGS = -g -std=c++20 -O3
TARGET = ./a.out
# TEST = test.cpp
TEST = research.cpp
SRC = cursach3.cpp



all: run

compile:
	${CC} ${SRC} -o ${TARGET} ${FLAGS}

run: compile
	${TARGET}

val: compile
	valgrind --leak-check=full ${TARGET}



test-compile:
	${CC} ${TEST} -o ${TARGET} ${FLAGS}

test: test-compile
	${TARGET}

test-val: test-compile
	valgrind --leak-check=full --track-origins=yes ${TARGET}