#pragma once

template <typename T> class Node {
public:
  T data;
  Node *left;
  Node *right;
  Node(T data, Node *left, Node *right);
  Node(T data);
  ~Node();
};

template <typename T> class BinaryTree {
public:
  T data;
  Node<T> *root;
  BinaryTree();
  BinaryTree<T>(Node<T> *root);
  ~BinaryTree();
};
