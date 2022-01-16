#include <iostream>

using std::cin;
using std::cout;
using std::endl;

class BinNode {
public:
	//constructor
	BinNode(int newVal = 0);
	//copy constructor
	BinNode(BinNode & orig);
	//destructor
	~BinNode() {}
	//copy assignment
	BinNode & operator=(BinNode & rhs);

	//setters and getters
	void setLeft(BinNode * newLeft) { pLeft = newLeft; }
	void setRight(BinNode * newRight) { pRight = newRight; }
	void setVal(int const newVal) { Value = newVal; }

	int getVal(void) const { return Value; }
	BinNode * & getLeft(void) { return pLeft; }
	BinNode * & getRight(void) { return pRight; }

protected:
	int Value;
	BinNode * pLeft;
	BinNode * pRight;
};

class BinTree {
public:
	//constructor
	BinTree();
	//copy constructor
	BinTree(BinTree & orig);
	//destructor
	~BinTree();
	//overloaded assignment
	BinTree & operator=(BinTree & rhs);

	//cleans out all nodes in memory-safe way
	//and resets root to nullptr
	//calls private version
	void clearTree(void);

	//copies nodes from orig to current tree; deep copy
	//make sure current tree is cleared first or memory leak may occur!
	//calls private version
	//unnecessary; assignment operator does essentially same thing
	//void copyTree(BinTree & orig);

	//adds a single value into the tree
	//calls private version
	virtual void addVal(int const newVal);

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
	BinNode * pRoot;
	
	//private versions called by public versions
	virtual void addVal(int const newVal, BinNode * & pTree);
	void clearTree(BinNode * & pTree);
	void inOrderTraversal(BinNode * & pTree);
	virtual void copyTree(BinNode * & pSource, BinNode * & pTarget);

private:
	//private version recursely searching for node
	void deleteVal(BinNode * & pTree, int const newVal);

	//deletes (frees) node pTree from the BST
	void deleteNode(BinNode * & pTree);

	//helper function for deleteNode
	//returns a reference to the node that will replace the node to be deleted
	//precondition: pTree must have a left child
	BinNode * & findReplacement(BinNode * pTree);

	//helper function for deleteNode
	//returns a pointer to the node that is the parent of the replacement node
	//precondition: pTree must have a left child
	BinNode * findReplacementParent(BinNode * PTree);
};