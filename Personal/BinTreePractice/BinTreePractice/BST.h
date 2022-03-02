#include <iostream>

using std::cin;
using std::cout;
using std::endl;

class BSTNode {

	friend class BST;
	friend class AVLTree;

public:
	//constructor
	BSTNode(int newVal = 0);
	//copy constructor
	BSTNode(BSTNode & orig);
	//destructor
	virtual ~BSTNode() {}
	//copy assignment
	BSTNode & operator=(BSTNode & rhs);

	//setters and getters
	void setLeft(BSTNode * newLeft) { pLeft = newLeft; }
	void setRight(BSTNode * newRight) { pRight = newRight; }
	void setVal(int const newVal) { Value = newVal; }

	int getVal(void) const { return Value; }
	virtual BSTNode * & getLeft(void) { return pLeft; }
	virtual BSTNode * & getRight(void) { return pRight; }

protected:

	int Value;
	BSTNode * pLeft;
	BSTNode * pRight;
};

class BST {
public:
	//constructor
	BST();
	//copy constructor
	BST(BST & orig);
	//destructor
	~BST();
	//overloaded assignment
	BST & operator=(BST & rhs);

	//cleans out all nodes in memory-safe way
	//and resets root to nullptr
	//calls private version
	void clearTree(void);

	//copies nodes from orig to current tree; deep copy
	//make sure current tree is cleared first or memory leak may occur!
	//calls private version
	//unnecessary; assignment operator does essentially same thing
	//void copyTree(BST & orig);

	//adds a single value into the tree
	//calls private version
	void addVal(int const newVal);

	//adds all values in an array to the tree
	//calls private version
	virtual void addVals(int newValArray[], int size);

	//returns true if tree is empty, false otherwise
	bool isEmpty(void);

	//prints out values in order
	//calls private version
	void inOrderTraversal(void);

	//searches for a value and if found, deletes it from the tree
	//calls private version
	virtual void deleteVal(int const newVal);

protected:
	BSTNode * pRoot;

	virtual BSTNode * makeNode(int const newVal);
	
	//private versions called by public versions
	void addVal(int const newVal, BSTNode * & pTree);
	void clearTree(BSTNode * & pTree);
	void inOrderTraversal(BSTNode * & pTree);
	virtual void copyTree(BSTNode * & pSource, BSTNode * & pTarget);

	//auxiliary tasks required for insertion into various derived trees
	virtual void auxInsertionTasks(BSTNode * & pTarget, int newVal) {}

private:
	//private version recursely searching for node
	void deleteVal(BSTNode * & pTree, int const newVal);

	//deletes (frees) node pTree from the BST
	void deleteNode(BSTNode * & pTree);

	//helper function for deleteNode
	//returns a reference to the node that will replace the node to be deleted
	//precondition: pTree must have a left child
	BSTNode * & findReplacement(BSTNode * pTree);

	//helper function for deleteNode
	//returns a pointer to the node that is the parent of the replacement node
	//precondition: pTree must have a left child
	BSTNode * findReplacementParent(BSTNode * PTree);
};