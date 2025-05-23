CC = g++-13
FLAGS = -g -std=c++20
TARGET = ./a.out
TEST = test.cpp
SRC = cursach3.cpp



all: run

compile:
	${CC} ${SRC} -o ${TARGET} ${FLAGS}

run: compile
	${TARGET}

val: compile
	valgrind --lecak-check=full



test-compile:
	${CC} ${TEST} -o ${TARGET} ${FLAGS}

test: test-compile
	${TARGET}

test-val: test-compile
	valgrind --leak-check=full --track-origins=yes ${TARGET}