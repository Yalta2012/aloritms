#pragma once
#include <iostream>
#include <cstdio>
#include <format>
#include <random>

template <typename T>class BinaryTree;

template <typename T>
class Node
{

  friend class BinaryTree<T>;

public:
  T data;
  Node *left;
  Node *right;
  Node *parent;
  Node(T data, Node *left, Node *right);
  Node(T data);
  ~Node();

// private:
  void Add(Node<T> *new_node);
  void Clear();
  int Higth();
  void Print();
  void FPrint(int layer);
  Node<T> * Find(T element);
  int NumberOfChildren();
  Node<T>*FindRightMin();
  void AddRoot(Node<T> *new_node, BinaryTree<T>*tree);
  void AddRandom(Node<T> *new_node, BinaryTree<T> *tree);
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
  void LeftRotate(Node<T>*);
  void RightRotate(Node<T>*);
  void InsertRoot(Node<T> *new_node);
  void InsertRoot(T new_element);
  void InsertRandom(Node<T> *new_node);
  void InsertRandom(T new_element);
};

#include "binarytree.tpp"