#include "redblacktree.h"

template <typename T>
RBNode<T>::RBNode(T value)
{
    color = Color::BLACK;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
    data = value;
}

template <typename T>
void RBNode<T>::Clear()
{
    if (left != nullptr)
    {
        left->Clear();
        delete left;
    }
    if (right != nullptr)
    {
        right->Clear();
        delete right;
    }
}

template <typename T>
void RBNode<T>::Print(int level)
{
    if (left != nullptr)
    {
        left->Print(level+1);
    }
    cout << data << " " << (color == Color::RED ? "R" : "B") << ":" <<level<< endl;
    if(right != nullptr){
        right->Print(level+1);
    }
}

////////////////////////////////////////////
template <typename T>
RBTree<T>::RBTree()
{
    root = nullptr;
}

template <typename T>
RBTree<T>::RBTree(RBNode<T> *node)
{
    root = node;
    node->color = Color::BLACK;
    node->left = nullptr;
    node->right = nullptr;
    node->parent = nullptr;
}

template <typename T>
RBTree<T>::RBTree(T value)
{
    root = new RBNode(value);
}

template <typename T>
RBTree<T>::~RBTree()
{
    Clear();
}

template <typename T>
void RBTree<T>::Clear()
{
    if (nullptr != root)
    {        
        root->Clear();
        delete root;
        root = nullptr;
    }
}

template <typename T>
void RBTree<T>::Print()
{
    if (root != nullptr)
    {
        root->Print(1);
    }
}

template <typename T>
void RBTree<T>::Insert(T data)
{
    Insert(new RBNode(data));
}

template <typename T>
void RBTree<T>::Insert(RBNode<T> *node)
{
    
    if (nullptr == node)
    return;
    node->left = nullptr;
    node->right = nullptr;
    node->parent = nullptr;


    // root is NULL
    if (nullptr == root)
    {
        root = node;
        node->color = Color::BLACK;
        return;
    }

    // finding right place
    // get p - parent
    RBNode<T> *p = root;
    node->color = Color::RED;
    while (nullptr == node->parent)
    {
        if (node->data < p->data)
            if (nullptr == p->left)
            {
                p->left = node;
                node->parent = p;
            }
            else
                p = p->left;
        else if (nullptr == p->right)
        {
            p->right = node;
            node->parent = p;
        }
        else
            p = p->right;
    }
    if (p->color == Color::BLACK)
        return;


    //get g - grabdparen and u - uncle
    RBNode<T> *g = p->parent;
    RBNode<T> *u = g->left == p ? g->right : g->left;

    // red uncle
    if (nullptr != u && u->color == Color::RED)
    {
        p->color = Color::BLACK;
        u->color = Color::BLACK;
        if (g != root)
            g->color = Color::RED;
        return;
    }

    // zig-zag
    if (p->data < g->data && node->data >= p->data)
    {
        g->left = node;

        node->parent = g;
        node->left = p;

        p->parent = node;
        p->right = nullptr;

        RBNode<T> *temp = node;
        node = p;
        p = temp;
    }
    else if (g->data <= p->data && p->data < node->data)
    {
        g->right = node;

        node->parent = g;
        node->right = p;

        p->parent = node;
        p->left = nullptr;

        RBNode<T> *temp = node;
        node = p;
        p = temp;
    }


    // straight line
    if (node->data < p->data && p->data < g->data)
    {
        g->color = Color::RED;
        p->color = Color::BLACK;
        RBNode<T>* gg = g->parent;
        if (nullptr == gg)
            root = p;
        else{
            if( g->data < gg->data )
                gg->left = p;
            else
                gg->right = p;
        }
        p->parent = g->parent;
        p->right = g;

        g->parent = p;
        g->left = nullptr;


    }
    else if (g->data <= p->data && p->data <= node->data)
    {
        g->color = Color::RED;
        p->color = Color::BLACK;
        if (g == root)
            root = p;

        RBNode<T>* gg = g->parent;
        if (nullptr == gg)
            root = p;
        else{
            if( g->data < gg->data )
                gg->left = p;
            else
                gg->right = p;
        }

        p->parent = g->parent;
        p->left = g;

        g->right = nullptr;
        g->parent = p;
    }
}