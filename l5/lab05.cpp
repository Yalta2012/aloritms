#include "binarytree.h"
#include <ctime>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

// class Node;
// class BinaryTree;

template <> inline int Node<int>::Fun() {
  int result = 0;
  if (nullptr != left)
    result += left->Fun();
  if (nullptr != right)
    result += right->Fun();
  if (data % 2 == 1 && nullptr != left && nullptr != right)
    result += 1;
  return result;
}

template <> inline int BinaryTree<int>::Fun() {
  if (nullptr == root)
    return 0;
  return root->Fun();
}

int main() {
  srand(time(0));

  ofstream outs1("standart_out.txt");
  ofstream outs2("random_out.txt");
  ofstream outs3("st_line_out.txt");
  ofstream outs4("rnd_line_out.txt");
  ofstream outs5("fun.txt");

  auto tree = new BinaryTree<int>();

  for (int i = 0; i < 5000; i++) {
    tree->Insert(random() % 10000);
    outs1 << i + 1 << "|" << tree->Higth() << endl;
  }
  delete tree;

  tree = new BinaryTree<int>();
  for (int i = 0; i < 5000; i++) {
    tree->InsertRandom(random() % 10000);
    outs2 << i + 1 << "|" << tree->Higth() << endl;
  }
  delete tree;

  tree = new BinaryTree<int>();
  for (int i = 0; i < 5000; i++) {
    tree->Insert(i);
    outs3 << i + 1 << "|" << tree->Higth() << endl;
  }
  delete tree;

  tree = new BinaryTree<int>();
  for (int i = 0; i < 5000; i++) {
    tree->InsertRandom(i);
    outs4 << i + 1 << "|" << tree->Higth() << endl;
  }

  tree->FPrint();
  cout << endl << endl << tree->Fun();
  delete tree;

  return 0;
}