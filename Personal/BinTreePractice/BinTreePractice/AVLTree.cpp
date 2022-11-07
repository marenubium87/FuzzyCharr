#include "AVLTree.h"

//********AVLNode class
//**********************

AVLNode::AVLNode(int newVal) : BSTNode(newVal) {
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
*/

AVLTree & AVLTree::operator=(AVLTree & rhs) {
	clearTree();
	copyTree(rhs.pRoot, pRoot);
	return *this;
}

AVLNode * AVLTree::makeNode(int const newVal) {
	return new AVLNode(newVal);
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

void AVLTree::auxInsertionTasks(BSTNode * & pTarget, int newVal) {
	updateHeight(pTarget);
	if (detectImbalance(pTarget)) {

		//rotations (rotations take care of updating heights post-rotation)
		if (newVal < pTarget->Value) {
			if (newVal < pTarget->pLeft->getVal()) {
				rotateRight(pTarget);
			}
			else {
				rotateLeftRight(pTarget);
			}
		}
		else {
			if (newVal > pTarget->pRight->getVal()) {
				rotateLeft(pTarget);
			}
			else {
				rotateRightLeft(pTarget);
			}
		}
	}
}

//returns true if pTarget's children violates balance criterion
bool AVLTree::detectImbalance(BSTNode * & pTarget) {
	int leftHeight = -1;
	int rightHeight = -1;

	if (pTarget->pLeft != nullptr) {
		leftHeight = (dynamic_cast<AVLNode *>(pTarget->pLeft))->height;
	}
	if (pTarget->pRight != nullptr) {
		rightHeight = (dynamic_cast<AVLNode *>(pTarget->pRight))->height;
	}

	return(leftHeight - rightHeight > 1 || leftHeight - rightHeight < -1);
}

void AVLTree::updateHeight(BSTNode * & pTarget) {
	int leftHeight = -1;
	int rightHeight = -1;

	if (pTarget->pLeft != nullptr) {
		leftHeight = (dynamic_cast<AVLNode *>(pTarget->pLeft))->height;
	}
	if (pTarget->pRight != nullptr) {
		rightHeight = (dynamic_cast<AVLNode *>(pTarget->pRight))->height;
	}

	(dynamic_cast<AVLNode *>(pTarget))->height = leftHeight - rightHeight > 0 ? 
		leftHeight + 1 : rightHeight + 1;
}

//performs a left rotation of pTarget with its RIGHT child
//requires a right child to exist
//also updates heights
void AVLTree::rotateLeft(BSTNode * & pTarget) {
	BSTNode * pTemp = pTarget;
	pTarget = pTarget->pRight;
	pTemp->pRight = pTarget->pLeft;
	pTarget->pLeft = pTemp;

	updateHeight(pTarget->pLeft);
	updateHeight(pTarget);
}

//performs a right rotation of pTarget with its LEFT child
//requires a left child to exist
//also updates heights
void AVLTree::rotateRight(BSTNode * & pTarget) {
	BSTNode * pTemp = pTarget;
	pTarget = pTarget->pLeft;
	pTemp->pLeft = pTarget->pRight;
	pTarget->pRight = pTemp;

	updateHeight(pTarget->pRight);
	updateHeight(pTarget);
}

//performs a left rotation on pTarget's LEFT child WITH
//the child's RIGHT child (in essence pTarget's L-R grandchild)
//THEN performs a right rotation of pTarget with its NEW LEFT child
//also updates heights
void AVLTree::rotateLeftRight(BSTNode * & pTarget) {
	rotateLeft(pTarget->pLeft);
	rotateRight(pTarget);
}

//performs a right rotation on pTarget's RIGHT child WITH
//the child's LEFT child (in essence pTarget's R-L grandchild)
//THEN performs a left rotation of pTarget with its NEW RIGHT child
//also updates heights
void AVLTree::rotateRightLeft(BSTNode * & pTarget) {
	rotateRight(pTarget->pRight);
	rotateLeft(pTarget);
}