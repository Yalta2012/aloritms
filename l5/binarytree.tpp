#include "binarytree.h"
#include <iostream>
#include <cstdio>
#include <format>
using namespace std;

template <typename T>
Node<T>::Node(T data, Node<T> *left, Node<T> *right, Node<T>*parent) : data(data), left(left), right(right),parent(parent)
{
}

template <typename T>
Node<T>::Node(T data) : Node<T>(data, nullptr, nullptr, nullptr)
{
}

template <typename T>
Node<T>::~Node() {}

template <typename T>
void Node<T>::Add(Node<T> *new_node)
{
  if (nullptr == new_node)
    return;
  if (new_node->data < data)
  {
    if (nullptr == left)
      left = new_node;
    else
      left->Add(new_node);
  }
  else
  {
    if (nullptr == right)
      right = new_node;
    else
      right->Add(new_node);
  }
  new_node->parent=this;
}

template <typename T>
void Node<T>::Clear()
{
  if (nullptr != left)
  {
    left->Clear();
    delete (left);
    left = nullptr;
  }
  if (nullptr != right)
  {
    right->Clear();
    delete (right);
    right = nullptr;
  }
}

template <typename T>
int Node<T>::Higth()
{
  int left_hight = 1, right_hight = 1;
  if (nullptr != left)
  {
    left_hight += left->Higth();
  }
  if (nullptr != right)
  {
    right_hight += right->Higth();
  }
  return max(left_hight, right_hight);
}

template <typename T>
void Node<T>::FPrint(int layer)
{

  if(nullptr == right)
  cout << data;
  else
  cout << std::format("{:-<5}",data);
  if (nullptr != right)
  {
    cout << "---";
    right->FPrint(layer + 1);
  }
  if (nullptr != left)
  {
    cout << endl;
    for (int i = 0; i < layer; i++)
    {
      
      for(int j = 0; j< 8;j++){
        // if (j==layer) cout<<"|";
        cout << " ";

      }
    }
    cout << "`-------";
    left->FPrint(layer + 1);
  }
}

template <typename T>
void Node<T>::Print()
{
if(nullptr != left)
  left->Print();
  cout<<data<<" ";
if(nullptr!=right)
  right->Print();
}

template <typename T> void
BinaryTree<T>::LNRTravel(){
  if(nullptr == root) return;
  root->Print();

}

template <typename T>
BinaryTree<T>::BinaryTree(Node<T> *root) : root(root), deep(0)
{
}

template <typename T>
BinaryTree<T>::BinaryTree() : root(nullptr), deep(0) {}

template <typename T>
BinaryTree<T>::~BinaryTree()
{
  Clear();
}

template <typename T>
void BinaryTree<T>::Insert(Node<T> *new_node)
{
  if (nullptr == root)
    root = new_node;
  else
    root->Add(new_node);
}

template <typename T>
void BinaryTree<T>::Insert(T new_element)
{
  Insert(new Node<T>(new_element));
}

template <typename T>
void BinaryTree<T>::FPrint()
{
  if (nullptr != root)
  {
    root->FPrint(0);
  }
  else
  {
    cout << "Empty tree" << endl;
  }
}

template <typename T>
void BinaryTree<T>::Clear()
{
  if (nullptr != root)
  {
    root->Clear();
    delete root;
    root = nullptr;
  }
}

template <typename T>
int BinaryTree<T>::Higth()
{
  int result = 0;
  if (nullptr != root)
  {
    result += root->Higth();
  }
  return result;
}
template <typename T>
Node<T> *Node<T>::Find(T element)
{
  Node<T> *result = nullptr;
  if (data == element)
    result = this;
  else if (element < data)
  {
    if (nullptr != left)
      result = left->Find(element);
  }
  else if (nullptr != right)
    result = right->Find(element);
  return result;
}

template <typename T>
Node<T> *BinaryTree<T>::Find(T element)
{
  if (nullptr != root)
    return root->Find(element);
  else
    return nullptr;
}

template <typename T>
int Node<T>::NumberOfChildren()
{
  int result = 0;
  if (nullptr != left)
  {
    result += left->NumberOfChildren() + 1;
  }
  if (nullptr != right)
  {
    result += right->NumberOfChildren() + 1;
  }
  return result;
}

template <typename T>
int BinaryTree<T>::NumberOfNodes()
{
  if (nullptr != root)
  {
    return root->NumberOfChildren() + 1;
  }
  else
    return 0;
}

template <typename T>
Node<T> * Node<T>::FindRightMin()
{
  if(left != nullptr){
    return left->FindRightMin(); 
  }
  else{
    return nullptr;
  }
}

template <typename T>
void BinaryTree<T>::Delete(Node<T>*node){

}

template <typename T>
void BinaryTree<T>:: Delete(T element){

}