#include "binTree.h"

int main() {
	BinTree alpha;
	BinTree beta;
	alpha.addVals(5);
	alpha.addVals(7);
	alpha.addVals(3);
	alpha.addVals(6);
	int myArr[] = { 5, 3, 7, 8, 9, 4, 2 };
	int len = sizeof(myArr) / sizeof(myArr[0]);
	alpha.clearTree();
	alpha.addVals(myArr, len);
	//beta.addVals(myArr, len);
	alpha.inOrderTraversal();
	beta = alpha;
	beta.inOrderTraversal();

	alpha.isEmpty();


	return 0;
}