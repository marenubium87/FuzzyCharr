//source for lab 6 tests
#include "lab6tests.h"

//wrapper to run all tests
void testWrapper() {
	int numTestsFailed = 0;
	int numTestsTotal = 0;
	cout << "Testing isEmpty...  ";
	if (isEmptyTest()) {
		cout << "PASSED";
	}
	else {
		cout << "FAILED";
		numTestsFailed++;
	}
	numTestsTotal++;
	cout << endl;

	cout << "Testing enqueue...  ";
	if (enqueueTest()) {
		cout << "PASSED";
	}
	else {
		cout << "FAILED";
		numTestsFailed++;
	}
	numTestsTotal++;
	cout << endl;

	/*
	cout << "Testing dequeue...  ";
	if (dequeueTest()) {
		cout << "PASSED";
	}
	else {
		cout << "FAILED";
		numTestsFailed++;
	}
	numTestsTotal++;
	cout << endl;

	cout << "Testing peek...  ";
	if (peekTest()) {
		cout << "PASSED";
	}
	else {
		cout << "FAILED";
		numTestsFailed++;
	}
	numTestsTotal++;
	cout << endl;

	cout << "Testing clear...  ";
	if (clearTest()) {
		cout << "PASSED";
	}
	else {
		cout << "FAILED";
		numTestsFailed++;
	}
	numTestsTotal++;
	cout << endl;

	cout << "Testing operators...  ";
	if (operatorTests()) {
		cout << "PASSED";
	}
	else {
		cout << "FAILED";
		numTestsFailed++;
	}
	numTestsTotal++;
	cout << endl << endl;
	*/

	cout << numTestsTotal - numTestsFailed << " of " << numTestsTotal
		<< " tests PASSED" << endl
		<< numTestsFailed << " of " << numTestsTotal << " tests FAILED"
		<< endl << endl;
}

//testing isEmpty function, returns true if test passed, false otherwise
bool isEmptyTest() {
	Queue A;
	if (!(A.pHead == nullptr && A.pTail == nullptr)) {
		return false;
	}
	if (A.isEmpty() == false) {
		return false;
	}
	QueueNode * someNode = new QueueNode("test");
	A.pHead = someNode;
	A.pTail = someNode;
	if (A.isEmpty() == true) {
		return false;
	}
	return true;
}

//testing enqueue function, returns true if test passed, false otherwise
bool enqueueTest() {
	Queue A;
	//confirm queue empty
	if (!A.isEmpty()) {
		return false;
	}

	//enqueue onto empty queue
	A.enqueue("A");
	if (A.pHead->getData() != "A" || A.pTail->getData() != "A" ||
		A.pHead->getNext() != nullptr || A.pTail->getNext() != nullptr) {
		return false;
	}

	//enqueue onto queue with one element
	A.enqueue("B");
	//is A still in the right place?
	QueueNode * pCurr = A.pHead;
	if (pCurr->getData() != "A") {
		return false;
	}
	//is B set up in the right place?
	pCurr = pCurr->getNext();
	if (pCurr->getData() != "B" || pCurr->getNext() != nullptr) {
		return false;
	}
	//is the tail pointer pointing to the right element?
	if (pCurr != A.pTail) {
		return false;
	}

	//enqueue onto queue with multiple elements
	A.enqueue("C");
	//is A still in the right place?
	pCurr = A.pHead;
	if (pCurr->getData() != "A") {
		return false;
	}
	//is B set up in the right place?
	pCurr = pCurr->getNext();
	if (pCurr->getData() != "B") {
		return false;
	}
	//is C set up in the right place?
	pCurr = pCurr->getNext();
	if (pCurr->getData() != "C" || pCurr->getNext() != nullptr) {
		return false;
	}
	//is the tail pointer pointing to the right element?
	if (pCurr != A.pTail) {
		return false;
	}

	//all tests completed
	return true;
}

//testing dequeue function, returns true if test passed, false otherwise
/*
bool dequeueTest() {
	Queue A;
}

//testing peek function, returns true if test passed, false otherwise
bool peekTest() {

}

//testing clear function, returns true if test passed, false otherwise
bool clearTest() {

}

//testing operators >> and <<, returns true if test passed, false otherwise
bool operatorTests() {

}
*/