//header file for Lab 4

#include <stdio.h>
#include <Windows.h>

typedef struct listNode {
	int data;
	struct listNode * pNext;
} ListNode;

//makes new node from heap memory and sticks value into it
//aux function for insertAtFront, insertAtRear
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

//takes an array of ordered lists and merges them in descending order
//returns the destination (merged) list
ListNode * mergeLists(ListNode * arrLists[], int numLists);