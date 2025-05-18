CC = g++-13
FLAGS = -g
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

test: compile-test
	${TARGET}

test-val: test-compile