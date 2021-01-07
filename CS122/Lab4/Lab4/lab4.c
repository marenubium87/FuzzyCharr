//source for lab 4

#include "lab4.h"

//makes new node from heap memory and sticks value into it
//aux function for insertAtFront, insertAtRear
ListNode * makeNode(int value) {
	ListNode * pMem = (ListNode *)malloc(sizeof(ListNode));
	pMem->data = value;
	pMem->pNext = NULL;
	return pMem;
}

//makes new node from heap memory with value stored in node,
//then places it into the front of pList
void insertAtFront(ListNode ** pList, int value) {
	ListNode * pMem = makeNode(value);
	//if list is empty
	if (*pList == NULL) {
		*pList = pMem;
	}
	//and if list is not empty
	pMem->pNext = *pList;
	*pList = pMem;
}

//makes new node from heap memory with value stored in node,
//and inserts it into list after the node pointed to by pTarget
void insertAfterTarget(ListNode * pTarget, int value) {

}