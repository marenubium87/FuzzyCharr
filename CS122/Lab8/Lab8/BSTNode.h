//header for BST Node class

#include <iostream>
#include <string>
#include <Windows.h>
#include <fstream>
#include <iomanip>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::ofstream;
using std::istream;
using std::ostream;

class BSTNode {
public:
	//constructor, default
	BSTNode(string newData = "");

	//getters
	string getData() const { return data; }
	BSTNode * & getLeft() { return pLeft; }
	BSTNode * & getRight() { return pRight; }

	//setters
	void setData(string const & newData) { data = newData; }
	void setLeft(BSTNode * const newLeft) { pLeft = newLeft; }
	void setRight(BSTNode * const newRight) { pRight = newRight; }

private:
	string data;
	BSTNode * pLeft;
	BSTNode * pRight;
};

//overloading stream insertion operator to output node
ostream & operator<<(ostream & lhs, BSTNode const & rhs);