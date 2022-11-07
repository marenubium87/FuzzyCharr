#include "BST.h"

class AVLNode : public BSTNode {
	//allows AVLTree to know/access AVLNode members/methods
	//but not vice versa; i.e. does *not* allow
	//AVLNode to know/access AVLTree members
	friend class AVLTree;

public:

	AVLNode(int newVal);
	AVLNode(AVLNode & orig);
	~AVLNode() {}
	AVLNode & operator=(AVLNode & rhs);

protected:

	int height;

private:

};

class AVLTree : public BST {
public:
	AVLTree() {}

	//ignoring by decree of cat
	//AVLTree(AVLTree & orig);

	~AVLTree() {}

	AVLTree & operator=(AVLTree & rhs);
	

	/*don't write this for now, by decree of Cat
	virtual void deleteNode(int const newVal);
	*/

protected:

	virtual AVLNode * makeNode(int const newVal);

	//protected version called by assignment operator
	//MAKE SURE target tree is EMPTY before copying!
	//***ignoring by decree of cat
	//virtual void copyTree(AVLNode * & pSource, AVLNode * & pTarget);

	//imbalance detection and rotations if necessary, plus height updating
	virtual void auxInsertionTasks(BSTNode * & pTarget, int newVal);

private:
	//returns true if pTarget's children violates balance criterion
	bool detectImbalance(BSTNode * & pTarget);

	void updateHeight(BSTNode * & pTarget);

	//performs a left rotation of pTarget with its RIGHT child
	void rotateLeft(BSTNode * & pTarget);

	//performs a right rotation of pTarget with its LEFT child
	void rotateRight(BSTNode * & pTarget);
	
	//performs a left rotation on pTarget's LEFT child WITH
	//the child's RIGHT child (in essence pTarget's L-R grandchild)
	//THEN performs a right rotation of pTarget with its NEW LEFT child
	void rotateLeftRight(BSTNode * & pTarget);

	//performs a right rotation on pTarget's RIGHT child WITH
	//the child's LEFT child (in essence pTarget's R-L grandchild)
	//THEN performs a left rotation of pTarget with its NEW RIGHT child
	void rotateRightLeft(BSTNode * & pTarget);
};