#include "binarytree.h"

template <typename T> Node<T>::Node(T data, Node *left, Node *right) {
  this.data = data;
  this.left = left;
  this.right = right;
}

template <typename T> Node<T>::Node(T data) { Node(data, nullptr, nullptr); }

template <typename T> Node<T>::~Node() {}
template <typename T> BinaryTree<T>::BinaryTree(Node<T> *root) {
  this.root = root;
}

template <typename T> BinaryTree<T>::BinaryTree() { BinaryTree(nullptr); }
