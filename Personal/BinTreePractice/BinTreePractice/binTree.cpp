#include "binTree.h"

//********BinNode class
//**********************

BinNode::BinNode(int newVal) {
	Value = newVal;
	pLeft = nullptr;
	pRight = nullptr;
}

BinNode::BinNode(BinNode & orig) {
	*this = orig;
}

BinNode & BinNode::operator=(BinNode & rhs) {
	Value = rhs.Value;
	pLeft = nullptr;
	pRight = nullptr;
	return *this;
}

//********BinTree class
//**********************

BinTree::BinTree() {
	pRoot = nullptr;
}

BinTree::BinTree(BinTree & orig) {
	*this = orig;
}

BinTree::~BinTree() {
	clearTree();
}

BinTree & BinTree::operator=(BinTree & rhs) {
	//delete original tree
	clearTree();
	//copy in new tree
	copyTree(rhs.pRoot, this->pRoot);
	return *this;
}

void BinTree::clearTree(void) {
	clearTree(pRoot);
	pRoot = nullptr;
}

//assumes the tree calling this fcn is empty!
//unnecessary; assignment operator does essentially same thing
/*
void BinTree::copyTree(BinTree & orig) {
	copyTree(orig.pRoot, pRoot);
}
*/

void BinTree::copyTree(BinNode * & pSource, BinNode * & pTarget) {
	if (pSource != nullptr) {
		pTarget = new BinNode(pSource->getVal());
		copyTree(pSource->getLeft(), pTarget->getLeft());
		copyTree(pSource->getRight(), pTarget->getRight());
	}
}

void BinTree::addVals(int const newVal) {
	addVals(newVal, pRoot);
}

void BinTree::addVals(int newValArray[], int size) {
	for (int i = 0; i < size; i++) {
		addVals(newValArray[i], pRoot);
	}
}

bool BinTree::isEmpty(void) {
	return pRoot == nullptr;
}

void BinTree::inOrderTraversal(void) {
	cout << "Current tree contents:" << endl << endl;
	inOrderTraversal(pRoot);
	cout << endl << endl;
}

void BinTree::inOrderTraversal(BinNode * & pTree) {
	if (pTree != nullptr) {
		inOrderTraversal(pTree->getLeft());
		cout << " " << pTree->getVal() << " ";
		inOrderTraversal(pTree->getRight());
	}
}

void BinTree::deleteVal(int const newVal) {
	deleteVal(pRoot, newVal);
}

void BinTree::deleteVal(BinNode * & pTree, int const newVal) {
	//traverse tree until we find newVal or conclude newVal does not exist
	if (pTree != nullptr) {
		if (newVal < pTree->getVal()) {
			deleteVal(pTree->getLeft(), newVal);

		}
		else if (newVal > pTree->getVal()) {
			deleteVal(pTree->getRight(), newVal);
		}

		//if node's value matches newVal,
		//we delete the node
		else {
			deleteNode(pTree);
		}
	}
}

void BinTree::addVals(int const newVal, BinNode * & pTree) {
	if (pTree == nullptr) {
		pTree = new BinNode(newVal);
	}
	else if (newVal < pTree->getVal()) {
		addVals(newVal, pTree->getLeft());
	}
	else {
		addVals(newVal, pTree->getRight());
	}
}

void BinTree::clearTree(BinNode * & pTree) {
	if (pTree != nullptr) {
		clearTree(pTree->getLeft());
		clearTree(pTree->getRight());
		delete pTree;
	}
}

void BinTree::deleteNode(BinNode * & pTree) {
	//is pTree a leaf?  if so just delete it
	if (pTree->getLeft() == nullptr && pTree->getRight() == nullptr) {
		delete pTree;
		pTree = nullptr;
	}
	//next two situations are if node to be deleted only has one child
	//simply then connect node's parent to its child and delete it
	else if (pTree->getLeft() != nullptr && pTree->getRight() == nullptr) {
		BinNode * pMem = pTree;
		pTree = pTree->getLeft();
		delete pMem;
	}

	else if (pTree->getLeft() == nullptr && pTree->getRight != nullptr) {
		BinNode * pMem = pTree;
		pTree = pTree->getRight();
		delete pMem;
	}

	//if node has two children, seek out the largest element in left subtree,
	//replace pTree's value with said element, then run delete on said element
	else {
		bool catWhims = false;
		if (catWhims) {
			BinNode * pMem = pTree;
			pTree = pTree->getLeft();
			while (pTree->getRight() != nullptr) {
				pTree = pTree->getRight();
			}
			//pTree's at the appropriate location now
			pMem->setVal(pTree->getVal());
			//now delete this new element
			deleteNode(pTree);
		}
		else {
			BinNode * pMem = pTree;
			//find a replacement node for pTree
			BinNode * & pReplace = findReplacement(pTree);

			//connect pTree to replacement
			pTree = pReplace;
			//connect replacement node's parent to left child
			pReplace = pReplace->getLeft();

			//copy over children
			pTree->setLeft(pMem->getLeft());
			pTree->setRight(pMem->getRight());

			//new links complete
			delete pMem;
		}
	}
}

BinNode * & BinTree::findReplacement(BinNode * & pTree) {
	pTree = pTree->getLeft();
	while (pTree->getRight() != nullptr) {
		pTree = pTree->getRight();
	}
	return pTree;
}