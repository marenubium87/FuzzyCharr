#include "treeTests.h"

int main() {
	AVLNode AVLNode1(5);
	AVLNode AVLNode2(AVLNode1);
	AVLNode AVLNode3(7);
	AVLNode3 = AVLNode1;

	AVLTree myTree(12);

	AVLTree myOtherTree;
	
	myOtherTree = myTree;



	return 0;
}