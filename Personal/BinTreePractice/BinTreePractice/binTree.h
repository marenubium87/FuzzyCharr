#include <iostream>


class BinNode {
public:
	//constructor
	BinNode(int newVal = 0);
	//copy constructor
	BinNode(BinNode & orig);
	//destructor
	~BinNode() {}
	//copy assignment
	BinNode & operator=(BinNode & rhs);

	//setters and getters
	void setVal(int newVal) { Value = newVal; }
	int getVal(void) const { return Value; }
	BinNode * & getLeft(void) { return pLeft; }
	BinNode * & getRight(void) { return pRight; }

private:
	int Value;
	BinNode * pLeft;
	BinNode * pRight;
};

class BinTree {
public:

private:


};