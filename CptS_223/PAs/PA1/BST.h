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
  int treeHeight;

  //helper to add a single element to BST in proper location,
  //keeps track of how many layers deep the new node is placed
  void addHelper(T val, Node<T> *&pTree, int & currH)
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
      addHelper(val, pTree->pLeft, currH);
    }
    else
    {
      addHelper(val, pTree->pRight, currH);
    }
    currH++;
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

  void printPreOrderHelper(Node<T> * pTree)
  {
    if(pTree != nullptr) {
      cout << pTree->value << " ";
      printPreOrderHelper(pTree->pLeft);
      printPreOrderHelper(pTree->pRight);
      
    }
  }

  //count passed in by ref from parent nodesCount fcn and thus
  //updates number of nodes as tree is traversed
  //depreciated, leaving here for posterity
  /*
  void nodesCountHelper(Node<T> * pTree, int & count) {
    if(pTree != nullptr) {
      nodesCountHelper(pTree->pLeft, count);
      nodesCountHelper(pTree->pRight, count);
      count++;
    }
  }
  */

  //essentially calculates the furthest distance any node in tree is
  //from the root; equivalent to height of tree
  //depreciated, leaving here for posterity
  /*
  void heightHelper(Node<T> * pTree, int & currH, int & maxH) {
    if(pTree != nullptr) {
      //if we successfully "descended" a level into the tree, increase height
      currH++;

      //is this a new record for height so far?
      if(currH > maxH) {
        maxH = currH;
      }

      heightHelper(pTree->pLeft, currH, maxH);
      heightHelper(pTree->pRight, currH, maxH);

      //exiting this level means "ascending" a level; adjust accordingly
      currH--;     
    }
  }
  */

public:
  BST()
  {
    root = nullptr;
    nodeCount = 0;
    treeHeight = -1;
  }

  //rule of 3 here
  BST(BST<T> &other)
  {
    root = nullptr;

    nodeCount = other.nodeCount;
    treeHeight = other.treeHeight;
    if (other.root == nullptr)
    {
      return;
    }
    cloneTree(other.root);
  }

  ~BST() {
    deleteTree(root);
  }

  BST<T> &operator=(BST &rhs)
  {
    //clear self
    this->deleteTree(root);
    this.root = nullptr;

    //copy other over
    cloneTree(rhs.root);
    nodeCount = rhs.nodeCount;
    treeHeight = rhs.treeHeight;
    return *this;
  }

  void add(T val)
  {
    //tracks how many layers deep the new node gets added at
    int currH = -1;
    addHelper(val, root, currH);

    //update tree nodes and height if applicable
    nodeCount++;
    if(currH > treeHeight) {
      treeHeight = currH;
    }
  }

  void print()
  {
    this->printPreOrder();
  }

  void printPreOrder() {
    printPreOrderHelper(root);
  }

  int nodesCount()
  {
    return nodeCount;
  }

  int height()
  {
    return treeHeight;
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
