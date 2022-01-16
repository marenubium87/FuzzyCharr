#include "treeTests.h"

int main() {
	BinTree alpha;
	BinTree beta;
	alpha.addVals(5);
	alpha.addVals(7);
	alpha.addVals(3);
	alpha.addVals(6);
	int myArr[] = { 9, 5, 3, 7, 2, 4, 11, 10, 13 };
	int len = sizeof(myArr) / sizeof(myArr[0]);
	alpha.clearTree();
	alpha.addVals(myArr, len);
	alpha.inOrderTraversal();

	alpha.deleteVal(9);
	alpha.inOrderTraversal();

	return 0;
}