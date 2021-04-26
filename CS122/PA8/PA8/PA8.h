//header for PA8

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cctype>

using std::cin;
using std::cout;
using std::fstream;
using std::ifstream;
using std::endl;
using std::string;

class Node {
public:
	Node(string newData = "");
	virtual ~Node() { }

	//return refs for left/right getters, so BST methods can modify pointers
	string getData() const { return data; }
	Node * & getLeft() { return pLeft; }
	Node * & getRight() { return pRight; }

	void setData(string & newData) { data = newData; }
	void setLeft(Node * newLeft) { pLeft = newLeft; }
	void setRight(Node * newRight) { pRight = newRight; }

	virtual void printData() = 0;
		
protected:
	string data;
	Node * pLeft;
	Node * pRight;
};

class TransactNode : public Node {
public:
	TransactNode(string newData, int newUnits);
	~TransactNode() { }

	int getUnits() const { return units; }
	void setUnits(int const newUnits) { units = newUnits; }

	void printData();

private:
	int units;
};

class BST {
public:
	BST() { pRoot = nullptr; }
	~BST() { destroyTree(pRoot); }

	//no reference here, we don't want this getter to change pRoot
	Node * getRoot() const { return pRoot; }
	void setRoot(Node * newRoot) { pRoot = newRoot; }

	//insert, calls private insert
	void insert(string newData, int newUnits);

	void inOrderTraversal();

	//returns reference to node with smallest units value
	//prec:  tree must not be empty!
	Node & findSmallest() { return findSmallest(*pRoot); }

	//returns reference to node with largest unitss value
	//prec:  tree must not be empty!
	Node & findLargest() { return findLargest(*pRoot); }

private:
	Node * pRoot;
	//private method to clean up tree; called by destructor
	void destroyTree(Node * & pTree);

	//private insert, called by public method
	void insert(string newData, int newUnits, Node * & pTree);

	//private in order traversal, prints to console, called by public method
	void inOrderTraversal(Node * pTree);

	//private search fcns, called by public methods
	Node & findSmallest(Node & currNode);
	Node & findLargest(Node & currNode);

};

class DataAnalysis {
public:
	DataAnalysis();
	~DataAnalysis() { closeFile(); }
	//performs all data analysis, calls other private fcns
	void runAnalysis();

private:
	BST treeSold;
	BST treePurchased;
	ifstream csvStream;

	//opens data file to populate trees with
	void openFile();
	//closes data file
	void closeFile();
	//reads one line from data file and stores results into
	//the three parameters listed
	void readLine(string & newType, int & newUnits, char & newTransact);

	void addToTree(string newType, int newUnits, char newTransact);

	//repeatedly calls readLine and populates both trees with data from file
	void populateTrees();

};