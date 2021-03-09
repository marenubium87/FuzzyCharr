//source for BST class

#include "BST.h"

//copy constructor, calls private recursive method
BST::BST(BST & orig) {
	pRoot = nullptr;
	copyTree(pRoot, orig.pRoot);
}

//overloaded assignment
BST & BST::operator=(BST & rhs) {
	//destroy old tree first to prevent memory leak
	destroyTree(pRoot);
	//copy over new tree
	pRoot = nullptr;
	copyTree(pRoot, rhs.pRoot);
	return *this;
}

//inserts node containing newData into appropriate location in tree
//calls private method insert (see below)
void BST::insert(string newData) {
	insert(newData, pRoot);
}

//extracts all nodes to string array dest
//precondition: dest is of size greater than number of elements in tree
//calls private method extract (see below)
void BST::extractAll(string dest[]) {
	extract(pRoot, dest);
}

//public methods for printing out nodes of tree
//calls private methods (see below)
void BST::printPreOrder() {
	printPreOrder(pRoot, nullptr);
}

void BST::printInOrder() {
	printInOrder(pRoot, nullptr);
}

void BST::printPostOrder() {
	printPostOrder(pRoot, nullptr);
}

//returns true if tree is empty, false otherwise
bool BST::isEmpty() {
	return pRoot == nullptr;
}

//private insertion method keeping track of our location in tree
//called by public method, runs recursively
void BST::insert(string newData, BSTNode * & pTree) {
	if (pTree == nullptr) {
		pTree = new BSTNode(newData);
		return;
	}
	else if (newData < pTree->getData()) {
		insert(newData, pTree->getLeft());
	}
	else {
		insert(newData, pTree->getRight());
	}
}

//extracts strings recursively from tree (in order) to string array dest
//includes a static, incrementing variable to keep track of which array
//element to insert into
void BST::extract(BSTNode * pTree, string dest[]) {
	static int i = 0;
	if (pTree == nullptr) {
		return;
	}
	//in order - left, center, right
	extract(pTree->getLeft(), dest);

	dest[i] = pTree->getData();
	i++;

	extract(pTree->getRight(), dest);

	//resets counter at the end of a stack of recursive calls
	if (pTree == pRoot) {
		i = 0;
	}
}

//private, recursive methods for printing out nodes of tree
//called by public methods
void BST::printPreOrder(BSTNode * pTree, BSTNode * pParent) {
	if (pTree == nullptr) {
		return;
	}

	//pre-order: current, left, right
	cout << "\"" << *pTree << "\", child of ";
	if (pParent == nullptr) {
		cout << "nobody.";
	}
	else {
		cout << "\"" << *pParent << "\".";
	}
	cout << endl;

	printPreOrder(pTree->getLeft(), pTree);
	printPreOrder(pTree->getRight(), pTree);
}

void BST::printInOrder(BSTNode * pTree, BSTNode * pParent) {
	if (pTree == nullptr) {
		return;
	}

	//in order: left, current, right
	printInOrder(pTree->getLeft(), pTree);

	cout << " \"" << *pTree << "\", child of ";
	if (pParent == nullptr) {
		cout << "nobody.";
	}
	else {
		cout << "\"" << *pParent << "\".";
	}
	cout << endl;
	printInOrder(pTree->getRight(), pTree);
}

void BST::printPostOrder(BSTNode * pTree, BSTNode * pParent) {
	if (pTree == nullptr) {
		return;
	}

	//post-order:  left, right, current
	printPostOrder(pTree->getLeft(), pTree);
	printPostOrder(pTree->getRight(), pTree);
	
	cout << "\"" << *pTree << "\", son of ";
	if (pParent == nullptr) {
		cout << "nobody.";
	}
	else {
		cout << "\"" << *pParent << "\".";
	}
	cout << endl;
}

//private recursive method for copying nodes, called by copy constructor
void BST::copyTree(BSTNode * & pTree, BSTNode * & pOrig) {
	if (pOrig != nullptr) {
		pTree = new BSTNode(pOrig->getData());
		copyTree(pTree->getLeft(), pOrig->getLeft());
		copyTree(pTree->getRight(), pOrig->getRight());
	}
}

//called by destructor, deletes each node via postorder traversal
void BST::destroyTree(BSTNode * & pTree) {
	if (pTree == nullptr) {
		return;
	}
	
	destroyTree(pTree->getLeft());
	destroyTree(pTree->getRight());

	delete pTree;
}

//overloaded insertion operator; prints out tree in-order
ostream & operator<<(ostream & lhs, BST & rhs) {
	rhs.printInOrder();
	return lhs;
}