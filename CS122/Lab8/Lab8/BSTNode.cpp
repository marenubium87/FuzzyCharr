//source for BST Node class

#include "BSTNode.h"

//constructor, default
BSTNode::BSTNode(string newData) {
	data = newData;
	pLeft = nullptr;
	pRight = nullptr;
}

//overloading stream insertion operator to output node
ostream & operator<<(ostream & lhs, BSTNode const & rhs) {
	lhs << rhs.getData();
	return lhs;
}