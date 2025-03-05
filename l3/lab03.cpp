#include "arrgen.h"
#include <chrono>
#include <iostream>
#include <fstream>
#include <cstdlib>

void PrintArray(int * array, size_t size){
	for(size_t i = 0;i<size; i++)
		std::cout<<array[i]<< " ";
	std::cout<<std::endl;
}

int * LineSearch(int * array, size_t size, int val){
	int * result = nullptr;
	
	for(size_t i = 0; i<size && result == nullptr; i++){
		if(array[i] == val)
			result = array+i;
	}

	return result;
}

int * JumpSearch(int * array, size_t size, int val, size_t jump){
	int * result = nullptr;
		for(size_t pos = 0; jump > 0 && result == nullptr; ){
			if(array[pos] == val)
				result = array+pos;
			else if (val < array[pos]){
				jump
			}
			else{
				pos+=jump;
			}
		}
	return result;
}

int * BinarySearch(int * array, size_t size, int val){
	int * result = nullptr;
	size_t low=0, high=size-1, pos = size/2;
	for(;(low<=high) && (result==nullptr) &&  low >=0 && high <= size-1; pos = (low+high)/2){
		if(array[pos] == val)
			result = array+pos;
		else if(val < array[pos])
			high = pos - 1;
		else
			low = 	pos +1;
	}
	return result;
}

int * FibonacciSort(int * array, size_t size, int val){
	int * result = nullptr;

	return result;
}

int * InterpolationSearch(int * array, size_t size, int val){
	int * result = nullptr;

	return result;
}
using namespace std;
using namespace ArrGen;
using namespace std::chrono;

int Comp(int a, int b){
	return b-a;
}
int main(){
    // ofstream outstream("out3.txt");
    // outstream << "Sort Name | Sequence | Size | Comparations | Time (mics) | Status\n";
    // auto begin = steady_clock::now();
    // auto end = steady_clock::now();
	size_t len = 100;
	int *a;
	a= (int*)malloc(len * sizeof(int));
	ArrGen::IncreasingSequence<int>(a,len,1,101);
	PrintArray(a,len);
	cout<<"\n";
	for(int i = -1; i<=130; i++){
	cout<<i<<")";
	int * res = BinarySearch(a,len,i);
	if(res) cout<<*res;
	else cout<<"NULL";
	cout<<"\n";
	}

	free(a);
	return 0;
}

#include "arrgen.cpp"