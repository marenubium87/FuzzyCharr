//header file for Lab 6

#include <iostream>
#include <Windows.h>
#include <string>
#include <fstream>
#include <cctype>
using std::cin;
using std::cout;
using std::istream;
using std::ostream;
using std::fstream;
using std::endl;
using std::string;
using std::getline;

int numTraversals;

template <typename Key, typename Value>
class BSTNode {
public:
	//constructor
	BSTNode(Key newKey, Value newValue);

	//getters; no setting necessary after construction
	Key getKey() const { return key; }
	Value getValue() const { return value; }
	BSTNode *& getLeft() { return pLeft; }
	BSTNode *& getRight() { return pRight; }

private:
	Key key;
	Value value;
	BSTNode * pLeft;
	BSTNode * pRight;
};

template <typename Key, typename Value>
BSTNode<Key, Value>::BSTNode(Key newKey, Value newValue) {
	key = newKey;
	value = newValue;
	pLeft = nullptr;
	pRight = nullptr;
}

template <typename Key, typename Value>
class BST {
public:
	//default constructor for debugging purposes
	BST();
	//constructs a BST based on the inputFile's contents
	BST(fstream & inputFile);
	//destructor
	~BST() { destroyTree(pRoot); }
	//copy constructor
	BST(BST & orig);
	//assignment
	BST & operator=(BST & rhs);

	//returns true if tree is empty, false otherwise
	bool isEmpty();

	//prints out entire BST in key: value pairs in order, calls private
	//printNode
	void print(void) const;

	//searches BST for key and returns the value corresponding to key
	//calls private search fcn
	Value search(Key inputKey) const;

	//used by constructor to insert new nodes into tree
	void insert(Key newKey, Value newValue);

private:
	BSTNode<Key, Value> * pRoot;

	//recursive fcn called by above insert to place nodes in correct location
	void insert(Key newKey, Value newValue, BSTNode<Key, Value> *& pTree);

	//destroys a tree recursively using post-order traversal
	//called by destructor and overloaded assignment operator
	void destroyTree(BSTNode<Key, Value> * & pTree);

	//recursive method for copying nodes, called by copy constructor
	//and overloaded assignment operator
	void copyTree(BSTNode<Key, Value> * & pTree, 
		BSTNode<Key, Value> * & pOrig);

	//called by public print function, prints current node, 
	//makes recursive calls
	void printNode(BSTNode<Key, Value> * pTree) const;

	//called by public search function, searches current node, 
	//makes recursive calls
	Value searchNode(Key inputKey, BSTNode<Key, Value> * pTree) const;
};

template <typename Key, typename Value>
BST<Key, Value>::BST() {
	pRoot = nullptr;
}

template <typename Key, typename Value>
BST<Key, Value>::BST(fstream & inputFile) {
	string tempStr = "";
	string delim = " ";
	Key tempKey;
	Value tempVal;
	while (getline(inputFile, tempStr)) {
		tempKey = tempStr[0];
		tempVal = tempStr.substr(tempStr.find(delim) + 1);
		insert(tempKey, tempVal);
	}
	inputFile.close();
}

template <typename Key, typename Value>
BST<Key, Value>::BST(BST<Key, Value> & orig) {
	pRoot = nullptr;
	copyTree(pRoot, orig.pRoot);
}

template <typename Key, typename Value>
BST<Key, Value> & BST<Key, Value>::operator=(BST<Key, Value> & rhs) {
	//destroys pre-existing tree first if applicable to prevent
	//memory leaking
	destroyTree(pRoot);

	copyTree(pRoot, rhs.pRoot);
	return *this;
}

template <typename Key, typename Value>
bool BST<Key, Value>::isEmpty() {
	return pRoot == nullptr;
}

//prints in order, calls private printNode
template <typename Key, typename Value>
void BST<Key, Value>::print(void) const {
	printNode(pRoot);
}

template <typename Key, typename Value>
Value BST<Key, Value>::search(Key inputKey) const {
	return searchNode(inputKey, pRoot);
}

//interface version, calls private version
template <typename Key, typename Value>
void BST<Key, Value>::insert(Key newKey, Value newValue) {
	insert(newKey, newValue, pRoot);
}

//private, called by interface version
template <typename Key, typename Value>
void BST<Key, Value>::insert(Key newKey, Value newValue,
	BSTNode<Key, Value> *& pTree) {

	if (pTree == nullptr) {
		pTree = new BSTNode<Key, Value>(newKey, newValue);
		return;
	}
	else if (newKey < pTree->getKey()) {
		insert(newKey, newValue, pTree->getLeft());
	}
	else {
		insert(newKey, newValue, pTree->getRight());
	}
}

template <typename Key, typename Value>
void BST<Key, Value>::destroyTree(BSTNode<Key, Value> * & pTree) {
	//post-order destruction
	if (pTree != nullptr) {
		destroyTree(pTree->getLeft());
		destroyTree(pTree->getRight());
		delete pTree;
		pTree = nullptr;
	}
}

template <typename Key, typename Value>
void BST<Key, Value>::copyTree(BSTNode<Key, Value> * & pTree,
	BSTNode<Key, Value> * & pOrig) {
	//perform pre-order traversal of original tree and insert
	//nodes into this tree

	if (pOrig != nullptr) {
		pTree = new BSTNode<Key, Value>(pOrig->getKey(), pOrig->getValue());
		copyTree(pTree->getLeft(), pOrig->getLeft());
		copyTree(pTree->getRight(), pOrig->getRight());
	}
}

template <typename Key, typename Value>
void BST<Key, Value>::printNode(BSTNode<Key, Value> * pTree) const {
	if (pTree != nullptr) {
		printNode(pTree->getLeft());
		cout << pTree->getKey() << ": " <<
			pTree->getValue() << endl;
		printNode(pTree->getRight());
	}
}

//called by public search function, searches current node, 
//makes recursive calls
template <typename Key, typename Value>
Value BST<Key, Value>::searchNode(Key inputKey, 
		BSTNode<Key, Value> * pTree) const{
	if (inputKey == pTree->getKey()) {
		return pTree->getValue();
	}
	else if (inputKey < pTree->getKey()) {
		numTraversals++;
		return searchNode(inputKey, pTree->getLeft());
	}
	else {
		numTraversals++;
		return searchNode(inputKey, pTree->getRight());
	}
}

