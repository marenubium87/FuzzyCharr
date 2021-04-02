#include <iostream>
#include <string>
#include <fstream>

using std::cin;
using std::cout;
using std::endl;
using std::string;

using std::istream;
using std::ostream;

template <typename Data>
class ListNode {
public:
	ListNode(Data newData);
	ListNode * & getNext() { return pNext; }
	Data getData() const { return data; }
	
	void setData(Data const newData) { data = newData; }
	void setNext(ListNode * newNext) { pNext = newNext; }

private:
	Data data;
	ListNode * pNext;
};

template <typename Data>
ListNode<Data>::ListNode(Data newData) {
	data = newData;
	pNext = nullptr;
}


template <typename Data>
class List {
public:
	List() { pHead = nullptr; }
	List(List & orig);
	~List() { clear(); }
	List & operator=(List & rhs);
	//creates ListNode with newData and inserts it in order into list
	//returns true if memory allocated and node inserted, false otherwise
	bool insertInOrder(Data newData);
	//sequentially searches for target in list
	//returns true if target was found and deleted, false otherwise
	bool deleteTarget(Data target);
	//returns true if list is empty, false otherwise
	bool isEmpty();
	
private:
	ListNode<Data> * pHead;
	void clear();
	void insertInOrder(ListNode<Data> * pMem, ListNode<Data> * & pList);
	bool deleteTarget(Data target, ListNode<Data> * & pList);

};

template <typename Data>
List<Data>::List(List<Data> & orig) {
	pHead = nullptr;
	*this = orig;
}

template <typename Data>
List<Data> & List<Data>::operator=(List<Data> & rhs) {
	//clear list to prevent memory leak
	clear();
	ListNode<Data> * pRightCurr = rhs.pHead;

	//insert dummy node into left to make loop easier
	pHead = new ListNode<Data>(0);
	ListNode<Data> * pLeftCurr = pHead;

	while (pRightCurr != nullptr) {
		pLeftCurr->setNext(new ListNode<Data>(pRightCurr->getData()));
		pRightCurr = pRightCurr->getNext();
		pLeftCurr = pLeftCurr->getNext();
	}

	//remove dummy node
	pLeftCurr = pHead;
	pHead = pHead->getNext();
	delete pLeftCurr;
	
	return *this;
}

//creates ListNode with newData and inserts it in order into list
//returns true if memory allocated and node inserted, false otherwise
template <typename Data>
bool List<Data>::insertInOrder(Data newData) {
	ListNode<Data> * pMem = new ListNode<Data>(newData);
	if (pMem == nullptr) {
		return false;
	}
	insertInOrder(pMem, pHead);
	return true;
}

//sequentially searches for target in list
//returns true if target was found and deleted, false otherwise
template <typename Data>
bool List<Data>::deleteTarget(Data target) {
	return deleteTarget(target, pHead);
}

//returns true if list is empty, false otherwise
template <typename Data>
bool List<Data>::isEmpty() {
	return pHead == nullptr;
}

template <typename Data>
void List<Data>::clear() {
	//delete from front repeatedly
	ListNode<Data> * pTemp = nullptr;
	while (pHead != nullptr) {
		pTemp = pHead;
		pHead = pHead->getNext();
		delete pTemp;
	}
}

template <typename Data>
void List<Data>::insertInOrder(ListNode<Data> * pMem, 
		ListNode<Data> * & pList) {

	ListNode<Data> * pCurr = pHead;
	if (pCurr == nullptr || pMem->getData() < pCurr->getData()) {
		//insert at front
		pMem->setNext(pCurr);
		pHead = pMem;
		return;
	}
	ListNode<Data> * pPrev = pCurr;
	pCurr = pCurr->getNext();
	while (pCurr != nullptr && pCurr->getData() < pMem->getData()) {
		pPrev = pCurr;
		pCurr = pCurr->getNext();
	}
	//pCurr is either at the end of list 
	//or at the element after the insertion location
	if (pCurr != nullptr) {
		
		//insert in middle needs one extra step vs insert at end
		pMem->setNext(pCurr);
		
	}
	//insert at end and middle both require this step
	pPrev->setNext(pMem);
}

template <typename Data>
bool List<Data>::deleteTarget(Data target, ListNode<Data> * & pList) {
	//is list empty?
	if (pHead == nullptr) {
		return false;
	}
	ListNode<Data> * pCurr = pHead;
	//delete at front
	if (pCurr->getData() == target) {
		pHead = pHead->getNext();
		delete pCurr;
		return true;
	}

	ListNode<Data> * pPrev = pCurr;
	pCurr = pCurr->getNext();

	while (pCurr != nullptr && pCurr->getData() != target) {
		pPrev = pCurr;
		pCurr = pCurr->getNext();
	}
	//at this point,
	//either nothing was found or pCurr is at the node that must be deleted

	//nothing was found
	if (pCurr == nullptr) {
		return false;
	}

	//delete in middle or at end
	pPrev->setNext(pCurr->getNext());
	delete pCurr;
	return true;
}