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
  Node(T data, Node *left, Node *right);
  Node(T data);
  ~Node();

private:
  void Add(Node<T> *new_node);
  void Clear();
  int Higth();
  void Print(int layer);
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
  void Print();
  void Clear();
  int Higth();
  Node<T> * Find(T element);
  int NumberOfNodes();

  int Fun();
};

#include "binarytree.tpp"