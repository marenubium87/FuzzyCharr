#include <iostream>



using std::cin;
using std::cout;
using std::endl;

//node data
typedef struct data {
	int value;
} Data;

//red-black node class
class RBTNode {
public:
	//default constructor
	RBTNode(int inValue = 0);
	//destructor
	~RBTNode() { }

private:
	Data mMyData;
	int height;
	bool isRed;
	RBTNode * mpLeft;
	RBTNode * mpRight;
};

//red-black tree class
class RBTree {
public:
	//default constructor
	RBTree() { mpRoot = nullptr; }
	//destructor
	~RBTree() { clear(); }

	bool isEmpty();
	void insert(int newData);

	//the following call private methods
	//clears out the tree and resets root to nullptr
	void clear();
	void prePrint();

private:
	RBTNode * mpRoot;

	//called by public method above
	void prePrint(RBTNode * pTree);
	void clear(RBTNode * pTree);
};