#pragma once
#include <iostream>
using namespace std;

enum class Color
{
    RED,
    BLACK
};

template <typename T>
class RBTree;
template <typename T>
class RBNode
{
    friend class RBTree<T>;

private:
    T data;
    RBNode<T> *left;
    RBNode<T> *right;
    RBNode<T> *parent;
    Color color;

    RBNode(T value);
    void Clear();
    void Print(int level);
};

template <typename T>
class RBTree
{
private:

public:
RBNode<T> *root;
    RBTree<T>();
    RBTree<T>(RBNode<T> *node);
    RBTree<T>(T value);
    ~RBTree<T>();
    void Insert(RBNode<T> *node);
    void Insert(T data);
    void Clear();
    void Print();
};
#include "redblacktree.tpp"