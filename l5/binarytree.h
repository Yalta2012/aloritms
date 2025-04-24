#pragma once

template <typename T>
class Node
{
  template <typename U>
  friend class BinaryTree;

public:
  T data;
  Node *left;
  Node *right;
  Node *parent;
  Node(T data, Node *left, Node *right, Node * parent);
  Node(T data);
  ~Node();

private:
  void Add(Node<T> *new_node);
  void Clear();
  int Higth();
  void Print();
  void FPrint(int layer);
  Node<T> * Find(T element);
  int NumberOfChildren();
  Node<T>*FindRightMin();

};

template <typename T>
class BinaryTree
{
public:
  int deep;
  Node<T> *root;
  BinaryTree();
  BinaryTree(Node<T> *);
  ~BinaryTree();
  void Insert(Node<T> *new_node);
  void Insert(T new_element);
  void FPrint();
  void Clear();
  int Higth();
  Node<T> * Find(T element);
  int NumberOfNodes();
  int Fun();
  void Delete(Node<T>*node);
  void Delete(T element);
  void LNRTravel();
};

#include "binarytree.tpp"