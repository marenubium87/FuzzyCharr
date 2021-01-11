//header file for Lab 4

#include <stdio.h>
#include <Windows.h>

typedef struct listNode {
	int data;
	struct listNode * pNext;
} ListNode;

//makes new node from heap memory and sticks value into it
//aux function for insertAtFront, insertAfterTarget
ListNode * makeNode(int value);

//makes new node from heap memory with value stored in node,
//then places it into the front of pList
//returns TRUE if operation successful, FALSE else
int insertAtFront(ListNode ** pList, int value);

//makes new node from heap memory with value stored in node,
//and inserts it into list after the node pointed to by pTarget
//prec:  pTarget must point to a node in the list
//returns TRUE if operation successful, FALSE else
int insertAfterTarget(ListNode * pTarget, int value);

//deletes the first element from the list and frees memory
void deleteAtFront(ListNode ** pList);

//deletes an entire list, freeing memory and resetting
//pList pointer to NULL
void deleteList(ListNode ** pList);

//aux function for mergeLists
//finds the highest value in 
//targetArray containing pointers to nodes with data and size targetSize
//and returns the index of the element containing highest value
//if there are multiple tied for highest, returns the first instance
//requires at least one pointer in targetArray to be non-NULL
int findHighestInArray(ListNode * targetArray[], int targetSize);

//aux function for mergeLists
//returns 1 if all elements in targetArray read NULL, i.e. all lists
//have terminated, 0 else
int allListsExhausted(ListNode * targetArray[], int targetSize);

//takes an array of ordered lists and merges them in descending order
//returns the destination (merged) list
ListNode * mergeLists(ListNode * arrLists[], int numLists);

//detects if there is a loop in a singly linked list, using 
//Floyd's cycle detection algorithm (tortoise and hare)
//returns 1 if a cycle is detected, 0 else
int detectCycle(ListNode * targetList);

//reverses target singly linked list in a single pass
//remember to pass in *location* of list
//returns the pointer to the beginning of the reversed list
ListNode * reverseList(ListNode ** targetList);