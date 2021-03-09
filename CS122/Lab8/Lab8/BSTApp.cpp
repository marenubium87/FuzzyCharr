//source for app to read and sort names

#include "BSTApp.h"

//wrapper to test tree operations in main
void treeOperations(void) {
	BST myTree;
	myTree.insert("November");
	myTree.insert("Echo");
	myTree.insert("Golf");
	myTree.insert("Juliet");
	myTree.insert("Sierra");
	myTree.insert("Foxtrot");
	myTree.insert("Victor");
	myTree.insert("Papa");
	myTree.insert("Tango");
	myTree.insert("Charlie");
	myTree.insert("Yankee");
	myTree.insert("Romeo");
	myTree.insert("Bravo");

	cout << "Test tree composition:" << endl
		<< "               N" << endl
		<< "          /          \\ " << endl
		<< "         E            S" << endl
		<< "       /   \\        /    \\ " << endl
		<< "      C     G      P      V" << endl
		<< "    /      / \\     \\     / \\  " << endl
		<< "   B      F   J     R   T   Y" << endl << endl;

	cout << "Traversing pre-order..." << endl << endl;
	myTree.printPreOrder();
	cout << endl;

	cout << "Traversing in-order..." << endl << endl;
	myTree.printInOrder();
	cout << endl;

	cout << "Traversing post-order..." << endl << endl;
	myTree.printPostOrder();
	cout << endl;

	BST myTreeCopy(myTree);
	cout << "Copied tree, traversing in-order..." << endl << endl;
	myTreeCopy.printInOrder();
	cout << endl;

	system("pause");
	system("cls");

	BST steakTree;
	steakTree.insert("I");
	steakTree.insert("am");
	steakTree.insert("steak");
	cout << "Steak tree, traversing in-order..." << endl << endl;

	steakTree.printInOrder();
	cout << endl;
	cout << "Setting steak tree equal to test tree (overloaded assignment)..."
		<< endl << endl;
	steakTree = myTree;
	cout << steakTree;

	system("pause");
	system("cls");
}

//reads names from input file until all names exhausted, and stores them
//into names array
//precondition:  namesArray has enough elements to store all entries from input
void readNames(ifstream & input, string namesArray[]) {
	int i = 0;
	while (!input.eof()) {
		getline(input, namesArray[i]);
		i++;
	}
}

//prints elements of target string array to console
void printArray(string target[]) {
	int i = 0;
	cout << "Target string array composition:" << endl << endl;
	while (target[i] != "") {
		cout << std::setw(3) << i << "  \"" << target[i] << "\"" << endl;
		i++;
	}
	cout << endl;
}

//uses a BST to sort source array
void BSTSort(string source[]) {
	BST maowmaow;
	int i = 0;

	//inserts (in-order) all elements of source array into tree
	while (source[i] != "") {
		maowmaow.insert(source[i]);
		i++;
	}

	maowmaow.extractAll(source);
}

//wrapper to test bst sort operations in main
void sortOperations(void) {
	ifstream input;
	input.open("input.txt", std::ios::in);
	string kitties[20];

	readNames(input, kitties);
	cout << "Read inputs from file." << endl << endl;
	printArray(kitties);
	cout << "Sorting array via BST." << endl << endl;
	BSTSort(kitties);
	printArray(kitties);
	system("pause");
}