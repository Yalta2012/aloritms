CC=g++-13
FLAGS=-g -std=c++20
SOURCE=lab05.cpp 
LIB=binarytree.tpp
TARG=./a.out

all: comp run

val: comp 
	valgrind --leak-check=full --track-origins=yes $(TARG)
style:
	clang-format -i *.cpp *.h *.tpp

run:
	$(TARG)

comp:
	$(CC) $(SOURCE) $(FLAGS) -o $(TARG)

