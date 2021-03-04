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
	cout << endl << endl;

	cout << numTestsTotal - numTestsFailed << " of " << numTestsTotal
		<< " tests PASSED" << endl << endl;

	if (numTestsFailed > 0) {
		cout << numTestsFailed << " of " << numTestsTotal << " tests FAILED"
			<< endl << endl;
	}
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
//assumes isEmptyTest was passed
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
//assumes previous tests were passed.
bool dequeueTest() {
	Queue A;
	QueueNode * pCurr = nullptr;
	string tempString;
	A.enqueue("A");
	A.enqueue("B");
	A.enqueue("C");

	tempString = A.dequeue();
	//does the correct string get returned?
	if (tempString != "A") {
		return false;
	}
	//is the head pointer point to the correct thing?
	pCurr = A.pHead;
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

	tempString = A.dequeue();
	//does the correct string get returned?
	if (tempString != "B") {
		return false;
	}
	//is the head pointer pointing to the correct thing?
	pCurr = A.pHead;
	if (pCurr->getData() != "C" || pCurr->getNext() != nullptr) {
		return false;
	}
	//is the tail pointer pointing to the right element?
	if (pCurr != A.pTail) {
		return false;
	}

	tempString = A.dequeue();
	//does the correct string get returned?
	if (tempString != "C") {
		return false;
	}
	//is the queue correctly empty now?
	if (A.pHead != nullptr || A.pTail != nullptr) {
		return false;
	}
	//all tests completed
	return true;
}

//testing peek function, returns true if test passed, false otherwise
//assumes all previous tests passed
bool peekTest() {
	Queue A;
	string tempString;
	A.enqueue("A");
	A.enqueue("B");
	
	tempString = A.peek();
	//makes sure tempString is populated correctly and that
	//the queue is still untouched
	if (tempString != "A" || A.pHead->getData() != "A") {
		return false;
	}
	return true;
}

//testing clear function, returns true if test passed, false otherwise
bool clearTest() {
	Queue A;
	A.enqueue("A");
	A.enqueue("B");
	A.enqueue("C");

	A.clear();
	if (A.pHead != nullptr || A.pTail != nullptr) {
		return false;
	}
	return true;
}