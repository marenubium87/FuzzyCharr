//source file for lab 3

#include "lab3.h"

//checks to see if stack is empty; returns true if so, false else
int isEmpty(StackNode * pStack) {
	if (pStack == NULL) {
		return TRUE;
	}
	else {
		return FALSE;
	}
}

//inserts a node with data of type double to top of stack
//node is allocated dynamically
//remember to pass in LOCATION of pStack when calling
void push(double value, StackNode ** pStack) {
	//allocate new node, store data
	StackNode * pNewNode = (StackNode *)malloc(sizeof(StackNode));
	pNewNode->data = value;

	//insert at front(top) operation
	pNewNode->pNext = *pStack;
	*pStack = pNewNode;
}

//deletes node from top (head) of stack
//remember to pass in LOCATION of pStack when calling
//WARNING!  stack cannot be empty when calling
void pop(StackNode ** pStack) {
	StackNode * pTemp = *pStack;
	//makes stack point to top's next element
	//then "forgets" previous top element
	//(but not in a memory-leaking way)
	*pStack = (*pStack)->pNext;
	free(pTemp);
}

//returns value from top of stack
double peek(StackNode * pStack) {
	return pStack->data;
}