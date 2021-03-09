//header for BST class

#include "BSTNode.h"

class BST {
public:
	//default constructor
	BST() { pRoot = nullptr; }

	//copy constructor
	BST(BST & orig);

	//destructor
	~BST() { destroyTree(pRoot); }

	//overloaded assignment
	BST & operator=(BST & rhs);

	//inserts node containing newData into appropriate location in tree
	//calls private method insert (see below)
	void insert(string newData);

	//extracts all nodes to string array dest
	//precondition: dest is of size greater than number of elements in tree
	//calls private method extract (see below)
	void extractAll(string dest[]);

	//public methods for printing out nodes of tree
	//calls private methods (see below)
	void printPreOrder();
	void printInOrder();
	void printPostOrder();

	//returns true if tree is empty, false otherwise
	bool isEmpty();

private:
	BSTNode * pRoot;

	//private insertion method keeping track of our location in tree
	//called by public method
	void insert(string newData, BSTNode * & pTree);

	//extracts strings recursively from tree (in order) to string array dest
	//includes a static, incrementing variable to keep track of which array
	//element to insert into
	void extract(BSTNode * pTree, string dest[]);

	//private, recursive methods for printing out nodes of tree
	//called by public methods... also keeps track of parent of
	//any particular node
	void printPreOrder(BSTNode * pTree, BSTNode * pParent);
	void printInOrder(BSTNode * pTree, BSTNode * pParent);
	void printPostOrder(BSTNode * pTree, BSTNode * pParent);

	//private recursive method for copying nodes, called by copy constructor
	void copyTree(BSTNode * & pTree, BSTNode * & pOrig);

	//called by destructor, deletes each node via postorder traversal
	void destroyTree(BSTNode * & pTree);
};

//overloaded insertion operator; prints out tree in-order
ostream & operator<<(ostream & lhs, BST & rhs);
