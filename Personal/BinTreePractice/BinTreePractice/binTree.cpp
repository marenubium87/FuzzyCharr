#include "binTree.h"

//BinNode class

BinNode::BinNode(int newVal) {
	Value = newVal;
	pLeft = nullptr;
	pRight = nullptr;
}

BinNode::BinNode(BinNode & orig) {
	Value = orig.Value;
	pLeft = nullptr;
	pRight = nullptr;
}

BinNode & BinNode::operator=(BinNode & rhs) {
	Value = rhs.Value;
	pLeft = nullptr;
	pRight = nullptr;
	return *this;
}