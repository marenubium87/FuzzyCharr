#include "BST.h"

//********BSTNode class
//**********************

BSTNode::BSTNode(int newVal) {
	Value = newVal;
	pLeft = nullptr;
	pRight = nullptr;
}

BSTNode::BSTNode(BSTNode & orig) {
	*this = orig;
}

BSTNode & BSTNode::operator=(BSTNode & rhs) {
	Value = rhs.Value;
	pLeft = nullptr;
	pRight = nullptr;
	return *this;
}

//********BST class
//**********************

BST::BST() {
	pRoot = nullptr;
}

BST::BST(BST & orig) {
	*this = orig;
}

BST::~BST() {
	clearTree();
}

BST & BST::operator=(BST & rhs) {
	//delete original tree
	clearTree();
	//copy in new tree
	copyTree(rhs.pRoot, pRoot);
	return *this;
}

void BST::clearTree(void) {
	clearTree(pRoot);
	pRoot = nullptr;
}

//assumes the tree calling this fcn is empty!
//unnecessary; assignment operator does essentially same thing
/*
void BST::copyTree(BST & orig) {
	copyTree(orig.pRoot, pRoot);
}
*/

BSTNode * BST::makeNode(int const newVal) {
	return new BSTNode(newVal);
}

void BST::copyTree(BSTNode * & pSource, BSTNode * & pTarget) {
	if (pSource != nullptr) {
		pTarget = makeNode(pSource->getVal());
		copyTree(pSource->getLeft(), pTarget->getLeft());
		copyTree(pSource->getRight(), pTarget->getRight());
	}
}

void BST::addVal(int const newVal) {
	addVal(newVal, pRoot);
}

void BST::addVals(int newValArray[], int size) {
	for (int i = 0; i < size; i++) {
		addVal(newValArray[i], pRoot);
	}
}

bool BST::isEmpty(void) {
	return pRoot == nullptr;
}

void BST::deleteVal(int const newVal) {
	deleteVal(pRoot, newVal);
}

void BST::deleteVal(BSTNode * & pTree, int const newVal) {
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

void BST::addVal(int const newVal, BSTNode * & pTree) {
	if (pTree == nullptr) {
		pTree = makeNode(newVal);
	}
	else if (newVal < pTree->getVal()) {
		addVal(newVal, pTree->getLeft());
	}
	else {
		addVal(newVal, pTree->getRight());
	}
	auxInsertionTasks(pTree, newVal);
}

void BST::clearTree(BSTNode * & pTree) {
	if (pTree != nullptr) {
		clearTree(pTree->getLeft());
		clearTree(pTree->getRight());
		delete pTree;
	}
}

void BST::deleteNode(BSTNode * & pTree) {
	//is pTree a leaf?  if so just delete it
	if (pTree->getLeft() == nullptr && pTree->getRight() == nullptr) {
		delete pTree;
		pTree = nullptr;
	}
	//next two situations are if node to be deleted only has one child
	//simply then connect node's parent to its child and delete it
	else if (pTree->getLeft() != nullptr && pTree->getRight() == nullptr) {
		BSTNode * pMem = pTree;
		pTree = pTree->getLeft();
		delete pMem;
	}

	else if (pTree->getLeft() == nullptr && pTree->getRight() != nullptr) {
		BSTNode * pMem = pTree;
		pTree = pTree->getRight();
		delete pMem;
	}

	//if node has two children, seek out the largest element in left subtree,
	//replace pTree's value with said element, then run delete on said element
	else {
		int catWhims = 2;
		//simple version, copies over replacement value and
		//deletes replacement node
		if (catWhims == 0) {
			BSTNode * pTmp = pTree;
			pTree = pTree->getLeft();
			while (pTree->getRight() != nullptr) {
				pTree = pTree->getRight();
			}
			//pTree's at the appropriate location now
			pTmp->setVal(pTree->getVal());
			//now delete this new element
			deleteNode(pTree);
		}
		//actually replaces pTree with replacement node
		//this version uses references
		//uses findReplacement as a helper fcn
		else if(catWhims == 1){
			BSTNode * pTmp = pTree;
			//find a replacement node for pTree
			BSTNode * & pReplace = findReplacement(pTree);

			//connect pTree to replacement
			pTree = pReplace;
			//connect replacement node's parent to left child
			pReplace = pReplace->getLeft();

			//copy over children
			pTree->setLeft(pTmp->getLeft());
			pTree->setRight(pTmp->getRight());

			//new links complete
			delete pTmp;
		}
		//this version doesn't use references
		//uses findReplacementParent as helper fcn
		else {
			BSTNode * pTmp = pTree;
			//pPar is the parent of the replacement node
			BSTNode * pPar = findReplacementParent(pTree);

			//this is the situation if pTree's left child is a leaf
			//or pTree's left child does not have a right child,
			//then pTree's left child is the replacement node
			if (pPar == pTmp) {
				pTree = pTree->getLeft();
				pTree->setRight(pTmp->getRight());
			}
			else {
				pTree = pPar->getRight();
				pPar->setRight(pPar->getRight()->getLeft());
				pTree->setLeft(pTmp->getLeft());
				pTree->setRight(pTmp->getRight());
				
			}
			delete pTmp;
			
		}
	}
}

//pTree is the node that is to be deleted
BSTNode * & BST::findReplacement(BSTNode * pTree) {
	//if pTree's left child is a leaf, or does not have a right child,
	//then it is the rightmost node of the left subtree
	if (pTree->getLeft()->getRight() == nullptr) {
		return pTree->getLeft();
	}
	pTree = pTree->getLeft();
	while (pTree->getRight()->getRight() != nullptr) {
		pTree = pTree->getRight();
	}
	//pTree is now parent of rightmost node in left subtree
	//since getters here return references and this fcn also returns a ref
	//this fcn *should* return the right pointer of
	//the replacement node's parent
	return pTree->getRight();
}

BSTNode * BST::findReplacementParent(BSTNode * pTree) {
	//this situation is if pTree's left child is the highest-valued node
	//in the left subtree and is thus the replacement node
	if (pTree->getLeft()->getRight() == nullptr) {
		return pTree;
	}
	else {
		pTree = pTree->getLeft();
		while (pTree->getRight()->getRight() != nullptr) {
			pTree = pTree->getRight();
		}
		return pTree;
	}
}

ostream & operator<<(ostream & lhs, BSTNode & rhs) {
	lhs << rhs.getVal() << " ";
	return lhs;
}

