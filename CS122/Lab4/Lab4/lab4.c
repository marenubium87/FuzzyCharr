//source for lab 4

#include "lab4.h"

//makes new node from heap memory and sticks value into it
//returns pointer to new node or NULL if memory was not allocated
//aux function for insertAtFront, insertAtRear
ListNode * makeNode(int value) {
	ListNode * pMem = NULL;
	pMem = (ListNode *)malloc(sizeof(ListNode));

	//only execute following if memory successfully allocated
	if (pMem != NULL) {
		pMem->data = value;
		pMem->pNext = NULL;
	}
	return pMem;
}

//makes new node from heap memory with value stored in node,
//then places it into the front of pList
//returns TRUE if operation successful, FALSE else
int insertAtFront(ListNode ** pList, int value) {
	ListNode * pMem = makeNode(value);
	if (pMem == NULL) {
		return FALSE;
	}

	//if list is not empty, set pMem's link
	if (*pList != NULL) {
		pMem->pNext = *pList;
	}
	*pList = pMem;

	return TRUE;
}

//makes new node from heap memory with value stored in node,
//and inserts it into list after the node pointed to by pTarget
//prec:  pTarget must point to a node in the list
//returns TRUE if operation successful, FALSE else
int insertAfterTarget(ListNode * pTarget, int value) {
	ListNode * pMem = makeNode(value);
	if (pMem == NULL) {
		return FALSE;
	}

	pMem->pNext = pTarget->pNext;
	pTarget->pNext = pMem;
	return TRUE;
}

//deletes the first element from the list and frees memory
void deleteAtFront(ListNode ** pList) {
	//nothing to delete
	if (*pList == NULL) {
		return;
	}
	ListNode * pTemp = *pList;
	*pList = (*pList)->pNext;
	free(pTemp);
}

//deletes an entire list, freeing memory and resetting
//pList pointer to NULL
void deleteList(ListNode ** pList) {
	
	//repeatedly delete and free first element
	while (*pList != NULL) {
		ListNode * pTemp = *pList;
		*pList = (*pList)->pNext;
		free(pTemp);
	}
}

//takes an array of ordered lists and merges them in descending order
//returns the destination (merged) list
ListNode * mergeLists(ListNode * arrLists[], int numLists) {
	ListNode * mergedList = NULL;

	//set up secondary array with pointers to each of the head elements
	//in the original list array... these will get incremented later
	ListNode ** arrListMarkers = 
		(ListNode **)malloc(numLists * sizeof(ListNode *));
	for (int i = 0; i < numLists; i++) {
		arrListMarkers[i] = arrLists[i];
		printf("%d ", arrListMarkers[i]->data);
	}

	

	return mergedList;
}

//reverses a singly linked list in a single 