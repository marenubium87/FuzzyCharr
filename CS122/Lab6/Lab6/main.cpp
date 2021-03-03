//CS122 Lab 6
//28 Feb 2021

#include "lab6tests.h"

int main() {
	Queue A;
	cout << A.isEmpty() << endl;
	A.printQueueRecursive();
	A.enqueue("I");
	string a1 = "Hi mom";

	cout << A.isEmpty() << endl;
	A.printQueueRecursive();
	A.enqueue("am");
	A.printQueueRecursive();
	A.enqueue("moo");
	A.printQueueRecursive();

	testWrapper();

	system("pause");
	return 0;
}