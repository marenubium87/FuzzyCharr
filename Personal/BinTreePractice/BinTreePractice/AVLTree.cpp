#include "AVLTree.h"

//********AVLNode class
//**********************

AVLNode::AVLNode(int newVal) : BinNode(newVal) {
	height = 0;
}

AVLNode::AVLNode(AVLNode & orig) {
	*this = orig;
}

AVLNode & AVLNode::operator=(AVLNode & rhs) {
	Value = rhs.Value;
	pLeft = nullptr;
	pRight = nullptr;
	height = 0;
	return *this;
}

//********AVLTree class
//**********************

//ignoring by decree of cat
/*
AVLTree::AVLTree(AVLTree & orig) {
	*this = orig;
}

AVLTree & AVLTree::operator=(AVLTree & rhs) {
	clearTree();
	copyTree(rhs.pRoot, pRoot);
	return *this;
}
*/

void AVLTree::addVal(int const newVal) {

}

void AVLTree::addVals(int newValArray[], int size) {

}

//ignoring by decree of cat
/*
void AVLTree::copyTree(AVLNode * & pSource, AVLNode * & pTarget) {
	if (pSource != nullptr) {
		pTarget = new AVLNode(pSource->getVal());
		copyTree(pSource->getLeft(), pTarget->getLeft());
		copyTree(pSource->getRight(), pTarget->getRight());
	}
}
*/