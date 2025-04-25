#include "binarytree.h"

using namespace std;

template <typename T>
Node<T>::Node(T data, Node<T> *left, Node<T> *right) : data(data), left(left), right(right), parent(nullptr)
{
}

template <typename T>
Node<T>::Node(T data) : Node<T>(data, nullptr, nullptr)
{
}

template <typename T>
Node<T>::~Node() {}

template <typename T>
void Node<T>::Add(Node<T> *new_node)
{
  if (nullptr == new_node)
    return;
  new_node->parent = this;

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

  if (nullptr == right)
    cout << data;
  else
    cout << std::format("{:-<5}", data);
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

      for (int j = 0; j < 8; j++)
      {
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
  if (nullptr != left)
    left->Print();
  cout << data << " ";
  if (nullptr != right)
    right->Print();
}

template <typename T>
void BinaryTree<T>::LNRTravel()
{
  if (nullptr == root)
    return;
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
  {
    root = new_node;
    root->parent = nullptr;
  }
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
Node<T> *Node<T>::FindRightMin()
{
  Node<T> *node_ptr = right;

  while (node_ptr->left)
    node_ptr = node_ptr->left;
  return node_ptr;
}

template <typename T>
void BinaryTree<T>::Delete(Node<T> *node)
{
  if (nullptr != node->left && nullptr != node->right)
  {
    Node<T> *right_min = node->FindRightMin();

    right_min->parent = node->parent;
    if (root == node)
      root = right_min;

    if (nullptr != node->parent)
      if (node->parent->left == node)
        node->parent->left = right_min;
      else
        node->parent->right = right_min;

    right_min->left = node->left;
    if (nullptr != right_min->left)
      right_min->left->parent = right_min;
  }
  else
  {
    Node<T> *child = nullptr;
    if (nullptr != node->left)
      child = node->left;
    else if (nullptr != node->right)
      child = node->right;

    if (nullptr != child)
      child->parent = node->parent;

    if (nullptr != node->parent)
    {

      if (node->parent->left == node)
        node->parent->left = child;
      else
      {
        node->parent->right = child;
      }
    }
  }

  delete (node);
}

template <typename T>
void BinaryTree<T>::Delete(T element)
{
  Node<T> *node_to_delete = Find(element);
  if (nullptr != node_to_delete)
    Delete(node_to_delete);
}

template <typename T>
void BinaryTree<T>::LeftRotate(Node<T> *node)
{

  if (nullptr == node->right)
    return;

  Node<T> *parent_ptr = node->parent;
  Node<T> *right_ptr = node->right;
  Node<T> *mid = right_ptr->left;
  Node<T> *temp;

  if (nullptr == parent_ptr)
  {
    root = right_ptr;
  }
  else
  {
    right_ptr->parent = parent_ptr;
    if (parent_ptr->right == node)
      parent_ptr->right = right_ptr;
    else
      parent_ptr->left = right_ptr;
  }

  node->right = mid;
  if (nullptr != mid)
    mid->parent = node;

  right_ptr->parent = parent_ptr;
  right_ptr->left = node;

  node->parent = right_ptr;
}

template <typename T>
void BinaryTree<T>::RightRotate(Node<T> *node)
{
  if (nullptr == node->left)
    return;

  Node<T> *parent_ptr = node->parent;
  Node<T> *left_ptr = node->left;
  Node<T> *mid = left_ptr->right;
  Node<T> *temp;

  if (nullptr == parent_ptr)
  {
    root = left_ptr;
  }
  else
  {
    left_ptr->parent = parent_ptr;
    if (parent_ptr->left == node)
      parent_ptr->left = left_ptr;
    else
      parent_ptr->right = left_ptr;
  }

  node->left = mid;
  if (nullptr != mid)
    mid->parent = node;

  left_ptr->parent = parent_ptr;
  left_ptr->right = node;

  node->parent = left_ptr;
}

template <typename T>
void BinaryTree<T>::InsertRoot(Node<T> *new_node)
{
  if (nullptr == root)
  {
    root = new_node;
    root->parent = nullptr;
  }
  else
    root->AddRoot(new_node, this);
}

template <typename T>
void BinaryTree<T>::InsertRoot(T new_element)
{
  InsertRoot(new Node<T>(new_element));
}

template <typename T>
void Node<T>::AddRoot(Node<T> *new_node, BinaryTree<T> *tree)
{
  if (nullptr == new_node)
    return;
  new_node->parent = this;

  if (new_node->data < data)
  {
    if (nullptr == left)
      left = new_node;
    else
      left->AddRoot(new_node, tree);
    tree->RightRotate(new_node->parent);
  }
  else
  {
    if (nullptr == right)
      right = new_node;
    else
      right->AddRoot(new_node, tree);
    tree->LeftRotate(new_node->parent);
  }
}

template <typename T>
void Node<T>::AddRandom(Node<T> *new_node, BinaryTree<T> *tree)
{
  if (nullptr == new_node)
    return;
  int a = this->NumberOfChildren()+1;
  // cout << a << " " << NumberOfChildren() + 1 << endl;
  if (a == 0)
  {
    AddRoot(new_node, tree);
  }
  else
  {
    if (new_node->data < data)
    {
      left->AddRandom(new_node, tree);
    }
    else
    {
      right->AddRandom(new_node, tree);
    }
  }
}

template <typename T>
void BinaryTree<T>::InsertRandom(Node<T> *new_node)
{
  if (nullptr == root)
  {
    root = new_node;
    root->parent = nullptr;
  }
  else
    root->AddRandom(new_node, this);
}

template <typename T>
void BinaryTree<T>::InsertRandom(T new_element)
{
  InsertRandom(new Node<T>(new_element));
}