//CS122 Lab 8
//8 Mar 2021

#include "BSTApp.h"

int main() {

	treeOperations();

	ifstream input;
	input.open("input.txt", std::ios::in);
	string kitties[20];
	readNames(input, kitties);
	BSTSort(kitties);
	
	system("pause");
	return 0;
}