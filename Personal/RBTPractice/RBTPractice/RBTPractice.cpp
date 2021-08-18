#include "RBTPractice.h"

/*******************************/
//RBTNode methods go here

RBTNode::RBTNode(int inValue) {
	mMyData.value = inValue;
	isRed = false;
	height = 0;
	mpLeft = nullptr;
	mpRight = nullptr;
}


/*******************************/
//RBTree methods go here

bool RBTree::isEmpty() {
	return mpRoot == nullptr;
}