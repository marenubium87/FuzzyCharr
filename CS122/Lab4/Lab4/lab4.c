//source for lab 4

#include "lab4.h"

//makes new node from heap memory and sticks value into it
//returns pointer to new node or NULL if memory was not allocated
//aux function for insertAtFront, insertAfterTarget
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

//aux function for mergeLists
//finds the highest value in 
//targetArray containing pointers to nodes with data and size targetSize
//and returns the index of the element containing highest value
//if there are multiple tied for highest, returns the first instance
//requires at least one pointer in targetArray to be non-NULL
int findHighestInArray(ListNode * targetArray[], int targetSize){
	//sets highest to first non-null array element
	int i = 0;
	int currHighestIndex = 0;
	while (targetArray[i] == NULL) {
		i++;
		currHighestIndex++;
	}
	int currHighest = targetArray[i]->data;
	
	//now cycle through rest of array to find highest element
	//pointed to by a non-null pointer
	for (; i < targetSize; i++) {
		if (targetArray[i] != NULL &&
				targetArray[i]->data > currHighest) {
			
			currHighest = targetArray[i]->data;
			currHighestIndex = i;
		}
	}
	return currHighestIndex;
}

//aux function for mergeLists
//returns 1 if all elements in targetArray read NULL, i.e. all lists
//have terminated, 0 else
int allListsExhausted(ListNode * targetArray[], int targetSize) {
	//loop through all lists
	for (int i = 0; i < targetSize; i++) {
		if (targetArray[i] != NULL) {
			return FALSE;
		}
	}
	//if code gets to here, all elements are indeed NULL
	return TRUE;
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
	}

	//inserts a dummy element at front of merged list to make while loop
	//easier.  will remove element later.
	insertAtFront(&mergedList, -1);
	ListNode * pMergedTail = mergedList;

	//do this as long as all the lists aren't exhausted
	int indexHighest = -1;
	while (!allListsExhausted(arrListMarkers, numLists)) {
		
		//find largest value and append to merged list's tail
		indexHighest = findHighestInArray(arrListMarkers, numLists);
		insertAfterTarget(pMergedTail, arrListMarkers[indexHighest]->data);
		pMergedTail = pMergedTail->pNext;

		//increment the appropriate pointer in the list markers array too
		arrListMarkers[indexHighest] = arrListMarkers[indexHighest]->pNext;
	}
	
	//remove the dummy element
	deleteAtFront(&mergedList);

	//clear memory
	free(arrListMarkers);

	return mergedList;
}

//detects if there is a loop in a singly linked list, using 
//Floyd's cycle detection algorithm (tortoise and hare)
//returns 1 if a cycle is detected, 0 else
int detectCycle(ListNode * targetList) {
	//define tortoise and hare
	ListNode * tortoise = targetList;
	ListNode * hare = targetList;
	while (hare != NULL) {
		hare = hare->pNext;
		//did the hare hit the end of the list moving forward once?
		if (hare == NULL) {
			return 0;
		}
		//move hare the second time and move tortoise up one
		hare = hare->pNext;
		tortoise = tortoise->pNext;
		//if the two ever point to the same node at any point
		//it means there is a cycle as the hare must have performed
		//at least one circuit in the loop and "caught up" with the tortoise
		if (hare == tortoise) {
			return 1;
		}
	}
	//if the code ever exits the loop it means the hare hit the end
	//of the list and thus there is no cycle
	return 0;
}

//reverses target singly linked list in a single pass
//remember to pass in *location* of list
//returns the pointer to the beginning of the reversed list
ListNode * reverseList(ListNode ** targetList) {
	//does targetList have 0 or 1 elements?
	if (*targetList == NULL || (*targetList)->pNext == NULL) {
		return targetList;
	}
	
	ListNode * pCurr = *targetList;
	ListNode * pNext = pCurr->pNext;
	//does targetList have exactly 2 elements?
	pCurr->pNext = NULL;

	if (pNext->pNext == NULL) {
		pNext->pNext = pCurr;
		*targetList = pNext;
		return targetList;
	}
	//if targetList has 3 or more elements, introduce support pointer, 
	//pSupp, which holds the position of pNext's pNext, else it will 
	//get lost when we "reverse" the direction of pNext's pNext pointer.
	//diagram:
	//	 ... ->	pC -> pN -> pS -> ...
	//   ... <- pC <- pN    pS -> ...
	//so now can increment pCurr to pNext and pNext to pSupp,
	//and move pSupp forward to the next pointer that needs to be "supported"
	ListNode * pSupp = pNext->pNext;
	while (pSupp != NULL) {
		pNext->pNext = pCurr;
		pCurr = pNext;
		pNext = pSupp;
		pSupp = pSupp->pNext;
	}
	//when pSupp becomes NULL, just need to flip pNext's pNext
	//one final time, and set head pointer
	pNext->pNext = pCurr;
	*targetList = pNext;
	return targetList;
}
