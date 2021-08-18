#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "dsexceptions.h"
#include <iostream>    // For NULL
#include <queue>  // For level order printout
#include <vector>
#include <algorithm> // For max() function
using namespace std;

// AvlTree class
//
// CONSTRUCTION: with ITEM_NOT_FOUND object used to signal failed finds
//
// ******************PUBLIC OPERATIONS*********************
// int size( )            --> Quantity of elements in tree
// int height( )          --> Height of the tree (null == -1)
// void insert( x )       --> Insert x
// void insert( vector<T> ) --> Insert whole vector of values
// void remove( x )       --> Remove x (unimplemented)
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted (in) order
// void printPreOrder( )  --> Print tree in pre order
// void printPostOrder( ) --> Print tree in post order
// void printInOrder( )   --> Print tree in *in* order
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class AvlTree
{
  public:
    AvlTree( ) : root( NULL )
      { }

    AvlTree( const AvlTree & rhs ) : root( NULL )
    {
        *this = rhs;
    }

    ~AvlTree( )
    {
       cout << " [!] Destructor called." << endl;
       makeEmpty( );
    }

    /**
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMin( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException( );
        return findMin( root )->element;
    }

    /**
     * Find the largest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMax( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException( );
        return findMax( root )->element;
    }

    /**
     * Returns true if x is found in the tree.
     */
    bool contains( const Comparable & x ) const
    {
        return contains( x, root );
    }

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty( ) const
    {
        return root == nullptr;
    }

    /**
     * Return number of elements in tree.
     */
    int size( )
    {
      return size( root );
    }

    /**
     * Return height of tree.
     *  Null nodes are height -1
     */
    int height( )
    {
      return height( root );
    }

    /**
     * Print the tree contents in sorted order.
     */
    void printTree( ) const
    {
        if( isEmpty( ) )
            cout << "Empty tree" << endl;
        else
            printInOrder( root );
    }

    /**
     * Print the tree contents in sorted order.
     */
    void printInOrder( ) const
    {
        if( isEmpty( ) )
            cout << "Empty tree" << endl;
        else
            printInOrder( root );
    }

    /**
     * Print the tree contents in pre order.
     */
    void printPreOrder( ) const
    {
        if( isEmpty( ) )
            cout << "Empty tree" << endl;
        else
            printPreOrder( root );
    }

    /**
     * Print the tree contents in post order.
     */
    void printPostOrder( ) const
    {
        if( isEmpty( ) )
            cout << "Empty tree" << endl;
        else
            printPostOrder( root );
    }

    /**
     * Make the tree logically empty.
     */
    void makeEmpty( )
    {
        makeEmpty( root );
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( const Comparable & x )
    {
        insert( x, root );
    }

    /**
     * Insert vector of x's into the tree; duplicates are ignored.
     */
    void insert( vector<Comparable> vals)
    {
      for( auto x : vals ) {
        insert( x, root );
      }
    }
     

    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    void remove( const Comparable & x )
    {
      if(!contains(x)) {
        return;
      }

      removeHelper(root, x);

    }


    /**
     * Deep copy. - or copy assignment operator
     *  Will be in part II
     */
    const AvlTree & operator=( const AvlTree & rhs )
    {
      cout << " [!] Copy *assignment* operator called." << endl;
      return *this;
    }


/*****************************************************************************/
  private:
    struct AvlNode
    {
        Comparable element;
        AvlNode   *left;
        AvlNode   *right;
        int       height;

        AvlNode( const Comparable & theElement, AvlNode *lt,
                                                AvlNode *rt, int h = 0 )
          : element( theElement ), left( lt ), right( rt ), height( h ) { }
    };

    AvlNode *root;

    /**
     * Internal method to count nodes in tree
     */
    int size( AvlNode * & t )
    {
      if(t == nullptr) {
        return 0;
      }
      else {
        return 1 + size(t->left) + size(t->right);
      }
    }

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( const Comparable & x, AvlNode * & t )
    {
       if(t == nullptr) {
         t = new AvlNode(x, nullptr, nullptr);
       }
       else if(x < t->element) {
         insert(x, t->left);
       }
       else {
         insert(x, t->right);
       }

       //check for inbalance
       if(detectImbalance(t)) {
         performRotation(t, x);
       }
       updateHeight(t);

    }

    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     *  You'll need this for deletes
     */
    AvlNode * findMin( AvlNode *t ) const
    {
      //empty tree scenario taken care of by calling method

      //furthest left element
      if(t->left == nullptr) {
        return t;
      }
      //not there yet, keep going
      else {
        return findMin(t->left);
      }
    }

    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    AvlNode * findMax( AvlNode *t ) const
    {
        //empty tree scenario taken care of by calling method

        //furthest right
        if(t->right == nullptr) {
          return t;
        }
        //not there yet
        else {
          return findMax(t->right);
        }
    }

    /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the tree.
     */
    bool contains( const Comparable & x, AvlNode *t ) const
    {
      //reached end, found nothing
      if(t == nullptr) {
        return false;
      }
      //found the correct element, stop searching
      else if(x == t->element) {
        return true;
      }
      //search left subtree
      else if(x < t->element) {
        return contains(x, t->left);
      }
      //search right subtree
      else {
        return contains(x, t->right);
      }
    }

/******************************************************/

    /**
     * Internal method to make subtree empty.
     * 
     */
    void makeEmpty( AvlNode * & t )
    {
        //post order deletion
        if(t != nullptr) {
          makeEmpty(t->left);
          makeEmpty(t->right);
          delete t;
        }
    }

    /**
     * Internal method to print a subtree rooted at t in sorted order.
     */
    void printInOrder( AvlNode *t ) const
    {
      if(t != nullptr) {
        printInOrder(t->left);
        cout << t->element << " ";
        printInOrder(t->right);
      }
      
    }

    /**
     * Internal method to print a subtree rooted at t in pre order.
     */
    void printPreOrder( AvlNode *t ) const
    {
      if(t != nullptr) {
        cout << t->element << " ";
        printPreOrder(t->left);
        printPreOrder(t->right);
      }
    }

    /**
     * Internal method to print a subtree rooted at t in post order.
     */
    void printPostOrder( AvlNode *t ) const
    {
      if(t != nullptr) {
        printPostOrder(t->left);
        printPostOrder(t->right);
        cout << t->element << " ";
      }
    }

    /**
     * Internal method to clone subtree.
     */
    AvlNode * clone( AvlNode *t ) const
    {
        if( t == NULL )
            return NULL;
        else
            return new AvlNode( t->element, clone( t->left ), clone( t->right ), t->height );
    }


    // Avl manipulations
    /**
     * Return the height of node t or -1 if NULL.
     */
    int height( AvlNode *t ) const
    {
      if(t == nullptr) {
        return -1;
      }
      else {
        return t->height;
      }
    }

    //returns true if absolute difference between left and right subtree
    //of node t is greater than 1
    bool detectImbalance(AvlNode *t) {
      if(t == nullptr) {
        return false;
      }
      else {
        return height(t->left) - height(t->right) > 1 ||
        height(t->left) - height(t->right) < -1;
      }
    }

    //helper to update the height of a given node based on heights of children
    void updateHeight(AvlNode *t) {
      if(t != nullptr) {
        t->height = max(height(t->left), height(t->right)) + 1;
      }
    }

    int max( int lhs, int rhs ) const
    {
        return lhs > rhs ? lhs : rhs;
    }

    /**
     * Rotate binary tree node with left child.
     * For AVL trees, this is a single rotation for case 1.
     * Update heights, then set new root.
     */
    void rotateWithLeftChild( AvlNode * & k2 )
    {
      AvlNode * temp = k2;
      k2 = k2->left;
      temp->left = k2->right;
      k2->right = temp;

      //update new child's height
      updateHeight(k2->right);
    }

    /**
     * Rotate binary tree node with right child.
     * For AVL trees, this is a single rotation for case 4.
     * Update heights, then set new root.
     */
    void rotateWithRightChild( AvlNode * & k1 )
    {
      AvlNode * temp = k1;
      k1 = k1->right;
      temp->right = k1->left;
      k1->left = temp;

      //update new child's height
      updateHeight(k1->left);
    }

    /**
     * Double rotate binary tree node: first left child.
     * with its right child; then node k3 with new left child.
     * For AVL trees, this is a double rotation for case 2.
     * Update heights, then set new root.
     */
    void doubleWithLeftChild( AvlNode * & k3 )
    {
      rotateWithRightChild(k3->left);
      rotateWithLeftChild(k3);
    }

    /**
     * Double rotate binary tree node: first right child.
     * with its left child; then node k1 with new right child.
     * For AVL trees, this is a double rotation for case 3.
     * Update heights, then set new root.
     */
    void doubleWithRightChild( AvlNode * & k1 )
    {
      rotateWithLeftChild(k1->right);
      rotateWithRightChild(k1);
    }

    //performs correct rotations based on value of insertion target
    //relative to the location that imbalance was detected
    void performRotation(AvlNode * & k, int target) {
      if(target < k->element) {
        if(target < k->left->element) {
          //single rotate right
          rotateWithLeftChild(k);
        }
        else {
          //left-right rotation
          doubleWithLeftChild(k);
        }
      }
      else {
        if(target < k->right->element) {
          //right-left rotation
          doubleWithRightChild(k);
        }
        else {
          rotateWithRightChild(k);
        }
      }
    }

    //performs correct rotations based on a deletion
    //relative to the location that imblanace was detected
    void performRotation(AvlNode * & k) {
      //after a deletion, which subtree has greater height?
      if(height(k->left) - height(k->right) > 0) {
        //does the left child have a right (grand)child?
        if(k->left->right != nullptr) {
          doubleWithLeftChild(k);
        }
        else {
          rotateWithLeftChild(k);
        }
      }
      else {
        //does the right child have a left (grand)child?
        if(k->right->left != nullptr) {
          doubleWithRightChild(k);
        }
        else {
          rotateWithRightChild(k);
        }
      }
    }

    //recursive method to remove element x (which exists AND is not the root)
    //from the tree
    void removeHelper(AvlNode * & pTree, const Comparable & x) {
      if(pTree->element > x) {
        removeHelper(pTree->left, x);
      }
      else if(pTree->element < x) {
        removeHelper(pTree->right, x);
      }
      //only remaining option is pTree is where we want to delete
      else {
        AvlNode * pTemp = pTree;
        
        if(pTree->right != nullptr) {
          if(pTree->left != nullptr) {
            //if the node pointed to by pTree has no nullptrs
            //plan:  replace element with largest element of left subtree,
            //then call remove fcn again on left subtree to erase element
            AvlNode * pReplace = findMax(pTree->left);
            pTree->element = pReplace->element;
            pReplace->element = x;
            removeHelper(pTree->left, x);
          }
          else {
            //pTree only has right ptr, connect pTree to pTree's child
            pTree = pTree->right;
            delete pTemp;
          }
        }
        else {
          if(pTree->left != nullptr) {
            //pTree only has left ptr, connect to child
            pTree = pTree->left;
            delete pTemp;
          }
          else {
            //no children, leaf node, just delete
            delete pTemp;
            pTree = nullptr;
          }
        }
      }

      //check for imbalances
      if(detectImbalance(pTree)) {
        performRotation(pTree);
      }

      updateHeight(pTree);
    }
};

#endif
