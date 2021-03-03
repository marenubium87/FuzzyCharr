//source for lab 6

#include "lab6.h"

//constructor
QueueNode::QueueNode(string const newData, QueueNode * pN) {
	data = newData;
	pNext = pN;
}

//copy constructor
QueueNode::QueueNode(QueueNode const & original) {
	this->pNext = nullptr;
	*this = original;
}

//overloaded assignment operator, copies data only
QueueNode & QueueNode::operator=(QueueNode const & rhs) {
	data = rhs.data;
	return *this;
}

//copy constructor
Queue::Queue(Queue const & original) {
	*this = original;
}

//overloaded assignment operator
Queue & Queue::operator=(Queue const & rhs) {
	//clears original queue to avoid memory leak
	clear();
	
	//enqueues elements of rhs to make a deep copy
	QueueNode * pCurr = rhs.pHead;
	while (pCurr != nullptr) {
		enqueue(pCurr->getData());
		pCurr = pCurr->getNext();
	}
	return *this;
}

//returns true if queue is empty, otherwise returns false
bool Queue::isEmpty() const {
	if (pHead == nullptr) {
		return true;
	}
	else {
		return false;
	}
}

//inserts a node with data newStr into the queue at the tail
//node is dynamically allocated from the heap
//returns true if memory was allocated for a node, false otherwise
bool Queue::enqueue(string const & newStr) {
	//create a new node
	QueueNode * pNewNode = new QueueNode(newStr);
	if (pNewNode == nullptr) {
		return false;
	}
	if (isEmpty()) {
		pHead = pNewNode;
	}
	else {
		pTail->setNext(pNewNode);
	}
	pTail = pNewNode;
	return true;
}

//deletes a node from the head of the queue 
	//and also returns the data in that node
	//precondition:  queue is not empty
string Queue::dequeue() {
	QueueNode * pCurr = pHead;
	//return the head element and remove it from queue
	string nodeContents = pCurr->getData();
	pHead = pCurr->getNext();
	//we don't leak memory in this household
	delete pCurr;
	
	//did we just delete the last node in the queue?
	if (pHead == nullptr) {
		pTail = nullptr;
	}
	return nodeContents;
}

//returns the data from the node at the front of the queue
//but does not delete said node from the queue
//precondition:  queue is not empty
string Queue::peek() {
	return pHead->getData();
}

//clears the entire queue, freeing memory
//invoked by destructor
void Queue::clear() {
	//essentially dequeues repeatedly but doesn't return data
	while (pHead != nullptr) {
		QueueNode * pCurr = pHead;
		pHead = pHead->getNext();
		delete pCurr;
	}
	//now queue is empty and head is null, so also clear tail
	pTail = nullptr;
}

//helper function for public printQueueRecursive,
//called by public printQueueRecursive
//prints out the data at the pCurr node and calls itself recursively
//to print out the next node, etc.
void Queue::printQueueRecursive(QueueNode * pCurr) {
	if (pCurr == nullptr) {
		cout << "NULL" << endl;
		return;
	}
	cout << "\"" << pCurr->getData() << "\"" << " -> ";
	printQueueRecursive(pCurr->getNext());
}

//recursively prints out the data in the queue
void Queue::printQueueRecursive() {
	cout << "HEAD -> ";
	printQueueRecursive(pHead);
}