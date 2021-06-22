/*
 * Binary Search Tree implementation - heavily lifted from https://gist.github.com/mgechev/5911348
 *
 * Simple integer keys and basic operations
 *
 * Aaron Crandall - 2016 - Added / updated:
 *  * Inorder, Preorder, Postorder printouts
 *  * Stubbed in level order printout
 *
 */

#ifndef _BST_H
#define _BST_H

#include <iostream>
#include <queue>
using namespace std;

/*
 *  Node datastructure for single tree node
 */
template <class T>
struct Node
{
  T value;
  Node *pLeft;
  Node *pRight;
};

/*
 * Binary Search Tree (BST) class implementation
 */
template <class T>
class BST
{

private:
  Node<T> *root;
  int nodeCount;

  //helper to add a single element to BST in proper location
  void addHelper(T val, Node<T> *&pTree)
  {
    if (pTree == nullptr)
    {
      //create & initialize new node
      pTree = new Node<T>;
      pTree->pLeft = nullptr;
      pTree->pRight = nullptr;
      pTree->value = val;
    }
    else if (val < pTree->value)
    {
      addHelper(val, pTree->pLeft);
    }
    else
    {
      addHelper(val, pTree->pRight);
    }
  }

  //helper to clone an entire tree
  void cloneTree(Node<T> *pOther)
  {
    if (pOther != nullptr)
    {
      addHelper(pOther->value, root);
      cloneTree(pOther->pLeft);
      cloneTree(pOther->pRight);
    }
  }

public:
  BST()
  {
    root = nullptr;
    nodeCount = 0;
  }

  //rule of 3 here
  BST(BST<T> &other)
  {
    root = nullptr;

    if (other.root == nullptr)
    {
      return;
    }
    cloneTree(other.root);
  }

  ~BST() {
    cout << "Entering destructor BST" << endl;
    deleteTree(root);
  }

  BST<T> &operator=(BST &rhs)
  {
    //clear self
    this->deleteTree(root);
    this.root = nullptr;

    //copy other over
    cloneTree(rhs.root);
    return *this;
  }

  void add(T val)
  {
    addHelper(val, root);
  }

  void print()
  {
    this->printPreOrder();
  }

  void printPreOrder()
  {
    cout << " [!] BST::printPreOrder currently unimplemented." << endl;
  }

  int nodesCount()
  {
    return 5;
  }

  int height()
  {
    cout << " [!] BST::height currently unimplemented." << endl;
    return (-1);
  }

  //post-order traversal deletion
  void deleteTree(Node<T> *pTree)
  {
    if (pTree == nullptr)
    {
      return;
    }

    deleteTree(pTree->pLeft);
    deleteTree(pTree->pRight);

    delete pTree;
  }
};

#endif
