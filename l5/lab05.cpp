#include "binarytree.h"
#include <iostream>
#include <vector>
using namespace std;

// class Node;
// class BinaryTree;

template<> inline int BinaryTree<int>::Fun(){
    return 0;
}

int main() {
  auto t = new BinaryTree<int>();
t->Insert(32);
t->Insert(16);
t->Insert(8);
t->Insert(40);
t->Insert(20);
t->Insert(32);
t->Insert(60);

  cout << t->NumberOfNodes() << endl;
  t->Print();
  delete t;
  return 0;
}