CC = g++-13
FLAGS = -g
TARGET = ./a.out
FILE = lab06.cpp

all: compile run

run:
	${TARGET}
	
compile:
	${CC} ${FILE} -o ${TARGET} ${FLAGS}

val: compile
	valgrind --leak-check=full ${TARGET}