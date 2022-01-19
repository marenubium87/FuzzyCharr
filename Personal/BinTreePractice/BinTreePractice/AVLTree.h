#include "binTree.h"

class AVLNode : public BinNode {
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

class AVLTree : public BinTree {
public:
	AVLTree() {}
	AVLTree(AVLTree & orig);
	~AVLTree() {}
	AVLTree & operator=(AVLTree & rhs);

	
	virtual void addVal(int const newVal);
	virtual void addVals(int newValArray[], int size);

	
	/*don't write this for now, by decree of Cat
	virtual void deleteNode(int const newVal);
	*/
protected:
	//protected version called by assignment operator
	//MAKE SURE target tree is EMPTY before copying!
	virtual void copyTree(AVLNode * & pSource, AVLNode * & pTarget);
private:
	//write rotations here
	//height updating fcn helpers?
	
};