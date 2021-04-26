//Source for PA8

#include "PA8.h"

Node::Node(string newData) {
	data = newData;
	pLeft = nullptr;
	pRight = nullptr;
}

//invokes base node constructor
TransactNode::TransactNode(string newData, int newUnits) : Node(newData) {
	units = newUnits;
}

void TransactNode::printData() {
	cout << std::left << std::setw(16) << data << "Units: " << units << endl;
}

//insert, calls private insert
void BST::insert(string newData, int newUnits) {
	insert(newData, newUnits, pRoot);
}

//prints out nodes in order (sorted by units)
void BST::inOrderTraversal() { 
	inOrderTraversal(pRoot);
	cout << "**" << endl << endl;
}

//private method to clean up tree; called by destructor
void BST::destroyTree(Node * & pTree) {
	//post-order destruction
	if (pTree != nullptr) {
		destroyTree(pTree->getLeft());
		destroyTree(pTree->getRight());
		delete pTree;
	}
}

//private insert, called by public method
void BST::insert(string newData, int newUnits, Node * & pTree) {
	if (pTree != nullptr) {
		if (newUnits < (dynamic_cast<TransactNode *>(pTree))->getUnits()) {
			insert(newData, newUnits, pTree->getLeft());
		}
		else {
			insert(newData, newUnits, pTree->getRight());
		}
	}
	else {
		pTree = new TransactNode(newData, newUnits);
	}
}

//private in order traversal, prints to console, called by public method
void BST::inOrderTraversal(Node * pTree) {
	if (pTree != nullptr) {
		inOrderTraversal(pTree->getLeft());
		pTree->printData();
		inOrderTraversal(pTree->getRight());
	}
}

//private search fcns, called by public methods
Node & BST::findSmallest(Node & currNode) {
	if (currNode.getLeft() == nullptr) {
		return currNode;
	}
	else {
		return findSmallest(*(currNode.getLeft()));
	}
}

Node & BST::findLargest(Node & currNode) {
	if (currNode.getRight() == nullptr) {
		return currNode;
	}
	else {
		return findLargest(*(currNode.getRight()));
	}
}

DataAnalysis::DataAnalysis() {
	treeSold.setRoot(nullptr);
	treePurchased.setRoot(nullptr);
	openFile();
}

//opens data file to populate trees with
void DataAnalysis::openFile() {
	csvStream.open("data.csv", std::ios::in);
}

//closes data file
void DataAnalysis::closeFile() {
	csvStream.close();
}

//reads one line from data file and stores results into
//the three parameters listed
void DataAnalysis::readLine(string & newType, int & newUnits,
		char & newTransact) {

	//read next line and store into tempString
	string tempString;
	std::getline(csvStream, tempString);

	//tokenize tempString...
	//find first substring up to comma, convert it to int as units
	newUnits = std::stoi(tempString.substr(0, tempString.find(',')));

	//cut off part of string describing number of units, so...
	tempString = tempString.substr(tempString.find(',') + 1);
	//tempString now only contains item type and transaction type

	//find substring containing type, then cut it off as well
	newType = tempString.substr(0, tempString.find(','));
	tempString = tempString.substr(tempString.find(',') + 1);

	//sold or purchased?
	newTransact = tolower(tempString[0]);
}

//repeatedly calls readLine and populates both trees with data from file
//also displays both trees to console
void DataAnalysis::populateTrees() {
	string type = "";
	int units = 0;
	char transact = '\0';

	//ignores the first line (column headings)
	csvStream.ignore(256, '\n');

	while (!csvStream.eof()) {
		//read and parse next line
		readLine(type, units, transact);
		//add to appropriate tree
		addToTree(type, units, transact);
	}

	//displays both trees
	cout << "  Purchases" << endl;
	treePurchased.inOrderTraversal();
	cout << "  Sales" << endl;
	treeSold.inOrderTraversal();
}

//auxiliary function for populateTrees; inserts a new node with the given
//parameters into the appropriate sold/purchased tree
void DataAnalysis::addToTree(string newType, int newUnits, char newTransact) {
	if (newTransact == 's') {
		treeSold.insert(newType, newUnits);
	}
	else {
		treePurchased.insert(newType, newUnits);
	}
}

//wrapper function to populate trees and print out lowest/highest 
void DataAnalysis::runAnalysis() {
	populateTrees();

	cout << "  Purchase Stats" << endl << endl;
	cout <<  "Smallest:  ";
	treePurchased.findSmallest().printData();
	cout << "Largest:  ";
	treePurchased.findLargest().printData();

	cout << endl;
	cout << "  Sales Stats" << endl << endl;
	cout  << "Smallest:  ";
	treeSold.findSmallest().printData();
	cout << "Largest:  ";
	treeSold.findLargest().printData();

}