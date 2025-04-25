#include "binarytree.h"
#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

// class Node;
// class BinaryTree;

template <>
inline int BinaryTree<int>::Fun()
{
  return 0;
}

int main()
{
  srand(time(0));
  auto t = new BinaryTree<int>();
  t->InsertRandom(32);
  t->FPrint();
  cout<<endl<< endl;
  t->InsertRandom(16);
  t->FPrint();
  cout<<endl<< endl;
  t->InsertRandom(5);
 

  // t->InsertRandom(8);
  // t->InsertRandom(5);
  // t->InsertRandom(31);
  // t->InsertRandom(19);
  // t->InsertRandom(17);
  // t->InsertRandom(5);
  // t->InsertRandom(5);
  // t->InsertRandom(5);

  // t->InsertRoot(32);
  // t->InsertRoot(16);
  // t->InsertRoot(5);
  // t->InsertRoot(8);
  // t->InsertRoot(5);
  // t->InsertRoot(31);
  // t->InsertRoot(19);
  // t->InsertRoot(17);
  // t->InsertRoot(5);
  // t->InsertRoot(5);
  // t->InsertRoot(5);

  t->FPrint();
  cout<<endl<< endl;

  // t->RightRotate(t->Find(32));
  // t->FPrint();
  // cout<<endl<< endl;
  
  // t->RightRotate(t->Find(32));
  // t->FPrint();
  // cout<<endl<< endl;
  
  // t->LeftRotate(t->Find(16));
  // t->FPrint();
  // cout << endl<< endl;


  // auto a = t->Find(20);
  // cout<<a->right->data<<endl;
  t->LNRTravel();

  cout<<endl;
  // cout<<endl<< endl;
  // cout<<rand() % (t->Find(17)->NumberOfChildren()+1) ;
  // a=a->FindRightMin();
  // if(a) cout<< a->data<<endl;
  delete t;
  return 0;
}