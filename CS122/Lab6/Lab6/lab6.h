//header for lab 6

#include <iostream>
#include <Windows.h>
#include <string>

using std::cin;
using std::cout;
using std::istream;
using std::ostream;
using std::endl;
using std::string;

//QueueNode defn
class QueueNode {
public:
	//constructor
	QueueNode(string const newData = "", QueueNode * pN = nullptr);

	//copy constructor
	QueueNode(QueueNode const & original);

	//destructor
	~QueueNode() { }

	//overloaded assignment operator
	QueueNode & operator=(QueueNode const & rhs);

	//accessors, mutators
	string getData() const { return data; }
	QueueNode * getNext() const { return pNext; }
	void setData(string const & newStr) { data = newStr; }
	void setNext(QueueNode * const & pN) { pNext = pN; }

private:
	string data;
	QueueNode * pNext;
};

class Queue {
public:
	//constructor
	Queue() { pHead = nullptr, pTail = nullptr; }
	//copy constructor
	Queue(Queue const & original);

	//destructor
	~Queue() { clear(); }

	//overloaded assignment operator
	Queue & operator=(Queue const & rhs);

	//returns true if queue is empty, otherwise returns false
	bool isEmpty() const;

	//inserts a node with data newStr into the queue at the tail
	//node is dynamically allocated from the heap
	//returns true if memory was allocated for a node, false otherwise
	bool enqueue(string const & newStr);

	//deletes a node from the head of the queue 
	//and also returns the data in that node
	//precondition:  queue is not empty
	string dequeue();

	//returns the data from the node at the front of the queue
	//but does not delete said node from the queue
	//precondition:  queue is not empty
	string peek();

	//recursively prints out the data in the queue
	void printQueueRecursive();

	//test fcns
	friend bool isEmptyTest();
	friend bool enqueueTest();
	friend bool dequeueTest();
	friend bool peekTest();
	friend bool clearTest();

private:
	//clears the entire queue, freeing memory
	//invoked by destructor
	void clear();
	//helper function for public printQueueRecursive
	//prints out the data at the pCurr node
	void printQueueRecursive(QueueNode * pCurr);

	QueueNode * pHead;
	QueueNode * pTail;
};

