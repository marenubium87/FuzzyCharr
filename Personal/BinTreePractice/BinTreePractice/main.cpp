#include "treeTests.h"

int main() {
	

	AVLTree myTree;

	int valArray[7] = { 30, 20, 10, 6, 2, 7, 25};

	vector<int> resultVector;

	myTree.addVals(valArray, 7);
	myTree.inOrderTraversal<ostream, int>(cout);
	myTree.inOrderTraversal<vector<int>, int>(resultVector);

	for (int val : resultVector) {
		cout << val << " ";
	}

	myTree.addVals(5, 8);

	return 0;
}