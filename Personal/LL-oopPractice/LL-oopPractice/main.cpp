#include "LL.h"

int main() {
	List<int> myList;

	myList.insertInOrder(5);
	myList.insertInOrder(3);
	myList.insertInOrder(7);
	myList.insertInOrder(6);

	myList.deleteTarget(3);
	myList.deleteTarget(6);

	List<int> myOtherList;
	myOtherList = myList;
	List<int> myThirdList(myOtherList);

	return 0;
}