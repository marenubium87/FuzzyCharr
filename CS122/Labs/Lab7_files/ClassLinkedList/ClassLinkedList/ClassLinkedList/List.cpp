#include "List.h"

// default constructor; will always set mpHead to NULL or nullptr
List::List()                    
{
	mpHead = nullptr;
}

// copy constructor - implicitly invoked copying a List object during construction of 
// another List object, or when a List object is passed-by-value - must perform a deep copy, 
// which means create new memory for each node copied!
List::List(const List &copyList)     
{
	//create dummy element at front to homogenize procedure for copying 
	//actual elements from original list
	ListNode * pCurr = new ListNode();
	mpHead = pCurr;

	//copying elements from original list
	ListNode * pCurrOrig = copyList.getHeadPtr();
	ListNode * pNewNode = nullptr;
	while (pCurrOrig != nullptr) {
		pNewNode = new ListNode(*pCurrOrig);
		pCurr->setNextPtr(pNewNode);
		pCurrOrig = pCurrOrig->getNextPtr();
		pCurr = pCurr->getNextPtr();
	}

	//delete dummy head
	pCurr = mpHead;
	mpHead = pCurr->getNextPtr();
	delete pCurr;
}

List::~List()                   // destructor - implicitly invoked when a List object leaves scope
{
	cout << "Inside List's destructor! Freeing each ListNode in the List!" << endl;
	destroyList();
}

// this function must allocate new memory for each of the nodes in rhs to construct "this" object
List & List::operator= (const List &rhs) // overloaded assignment operator - must perform a deep copy
{
	//if this list is currently non-empty, destroy list to prevent a memory leak
	if (mpHead != nullptr) {
		destroyList();
	}
	//create dummy element at front to homogenize procedure for copying 
	//actual elements from original list
	ListNode * pCurr = new ListNode();
	mpHead = pCurr;

	//copying elements from original list
	ListNode * pCurrOrig = rhs.getHeadPtr();
	ListNode * pNewNode = nullptr;
	while (pCurrOrig != nullptr) {
		pNewNode = new ListNode(*pCurrOrig);
		pCurr->setNextPtr(pNewNode);
		pCurrOrig = pCurrOrig->getNextPtr();
		pCurr = pCurr->getNextPtr();
	}

	//delete dummy head
	pCurr = mpHead;
	mpHead = pCurr->getNextPtr();
	delete pCurr;

	return (*this);
}

// getter
ListNode * List::getHeadPtr() const     // returns a copy of the address stored in mpHead
{
	return mpHead;
}

// setter
void List::setHeadPtr(ListNode * const pNewHead) // modifies mpHead
{
	mpHead = pNewHead;
}

// This function creates a new ListNode on the heap, and uses the ListNode constructor to initialize the node!
bool List::insertAtFront(const int newData)     // inserts newData at the beginning or front of the list
{
	ListNode *pMem = makeNode(newData);
	bool success = false;                   // C++ has built in bool types - false, true

	if (pMem != nullptr)
	{
		success = true; // allocated memory successfully
		// pMem is pointing to a ListNode object, but a List object does not have direct access to it; must use a setter!
		pMem->setNextPtr(mpHead);
		mpHead = pMem;
	}

	return success;
}

// insert newData in ascending order
// precondition - list is already ordered, else this function makes no sense
bool List::insertInOrder(const int newData)     
{
	bool success = false;
	ListNode * pMem = makeNode(newData);

	if (pMem != nullptr) {
		success = true;  //allocated memory successfully
			
		//are we inserting into an empty list?
		if (mpHead == nullptr) {
			mpHead = pMem;
			return success;
		}

		ListNode * pCurr = mpHead;

		//if element to be inserted is <= head element, then
		//this operation is equivalent to insert at front
		if (newData <= mpHead->getData()) {
			pMem->setNextPtr(mpHead);
			mpHead = pMem;
			return success;
		}
		
		ListNode * pPrev = pCurr;
		pCurr = pCurr->getNextPtr();
		//increment these two pointers to adjacent nodes until pCurr reaches
		//the end of the list, or until pCurr is the first element that
		//newData is less than or equal to
		while (pCurr != nullptr && newData > pCurr->getData()) {
			pPrev = pCurr;
			pCurr = pCurr->getNextPtr();
		}
		//so now the element containing newData needs to be inserted
		//between pPrev and pCurr
		pMem->setNextPtr(pCurr);
		pPrev->setNextPtr(pMem);

		return success;
	}

	return success;
}

// inserts newData at the end of the list
bool List::insertAtEnd(const int newData)       
{
	bool success = false;
	ListNode * pMem = new ListNode(newData);
	if (pMem != nullptr) {
		success = true;

		//is the list empty?
		if (mpHead == nullptr) {
			mpHead = pMem;
			return success;
		}

		//move pCurr through list until it finds last element
		ListNode * pCurr = mpHead;
		while (pCurr->getNextPtr() != nullptr) {
			pCurr = pCurr->getNextPtr();
		}
		//pCurr's pointing at the last element in the list
		pCurr->setNextPtr(pMem);
		
		return success;
	}
	
	return success;
}

// determines if the list is empty;  
// returns true if the list is empty; false otherwise
bool List::isEmpty()                           
{
	return (mpHead == nullptr);
}

// deletes the node at the front of the list and returns a copy of the data
// precondition: list must not be empty
int List::deleteAtFront()                       
{
	int data = 0;

	data = mpHead->getData();
	ListNode * pCurr = mpHead;
	mpHead = mpHead->getNextPtr();
	delete pCurr;

	return data;
}

// deletes the node with data == searchValue;
// returns true if the value was found; false otherwise
// precondition: list must not be empty
bool List::deleteNode(const int searchValue)    
{
	bool success = false;

	//is the list empty?
	if (mpHead == nullptr) {
		//does nothing, will eventually return success as false at end
	}

	//does the list have only one element?
	else if (mpHead->getNextPtr() == nullptr) {
		if (searchValue == mpHead->getData()) {
			deleteAtFront();
			success = true;
		}
	}
	//is the element to be deleted the first element?
	else if (mpHead->getData() == searchValue) {
		ListNode * pTemp = mpHead;
		mpHead = mpHead->getNextPtr();
		delete pTemp;
		success = true;
	}
	else {
		//set up pPrev and pCurr; if pCurr is found to require deletion,
		//link pPrev to pCurr's pNext and delete pCurr
		ListNode * pPrev = mpHead;
		ListNode * pCurr = pPrev->getNextPtr();

		while (pCurr->getNextPtr() != nullptr && pCurr->getData() != searchValue) {
			pPrev = pCurr;
			pCurr = pCurr->getNextPtr();
		}

		//so now either pCurr is the last element or pCurr contains
		//the search value (or both), so make a check
		if (pCurr->getData() == searchValue) {
			//perform deletion procedure
			pPrev->setNextPtr(pCurr->getNextPtr());
			delete pCurr;
			success = true;
		}
	}

	return success;
}

// deletes the node at the end of the list and returns a copy of the data
// precondition: list must not be empty
int List::deleteAtEnd()                         
{
	int data = 0;

	//is there only one element in the list?
	if (mpHead->getNextPtr() == nullptr) {
		ListNode * pTemp = mpHead;
		data = pTemp->getData();
		mpHead = mpHead->getNextPtr();
		delete pTemp;
	}
	else {
		ListNode * pPrev = mpHead;
		ListNode * pCurr = pPrev->getNextPtr();

		//maneuver pPrev and pCurr so that pCurr points to last element in list
		while (pCurr->getNextPtr() != nullptr) {
			pPrev = pCurr;
			pCurr = pCurr->getNextPtr();
		}
		//so now pCurr's at the last element in the list
		data = pCurr->getData();
		pPrev->setNextPtr(pCurr->getNextPtr());
		delete pCurr;
	}

	return data;
}

// visits each node, print the node's data
void List::printList()                          
{
	ListNode *pCur = mpHead;

	while (pCur != nullptr)
	{
		cout << pCur->getData() << endl;
		pCur = pCur->getNextPtr();
	}
}


//////////// private member functions! //////////////

// allocates memory for a Listnode; initializes the memory with newData
ListNode * List::makeNode(const int newData)    // will only call within insert functions
{
	ListNode *pMem = new ListNode(newData);  // ListNode constructor is invoked!

	return pMem;
}

// we created this function so that we could use recursion to delete the nodes!
void List::destroyListHelper(ListNode * const pMem)
{
	if (pMem != nullptr)
	{
		destroyListHelper(pMem->getNextPtr());
		delete pMem;    // delete from the back of list to the front!
	}
}

// deletes each node to free memory; will call in the destructor
void List::destroyList()                        
{
	destroyListHelper(mpHead);
}