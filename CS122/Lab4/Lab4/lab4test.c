//source for lab 4 tests and aux

#include "lab4test.h"

//list visualization.  prints out targetList to console
void printList(ListNode * targetList) {
	ListNode * pCurr = targetList;
	
	printf("Current List Contents:\n");
	while (pCurr != NULL) {
		printf("%d -> ", pCurr->data);
		pCurr = pCurr->pNext;
	}
	printf("NULL\n\n");
}





//wrapper for the merge lists function test
void task4wrapper(void) {
	ListNode * arrLists[5] = { NULL };
	insertAtFront(&arrLists[0], 3);
	insertAtFront(&arrLists[0], 5);
	insertAtFront(&arrLists[0], 6);
	insertAtFront(&arrLists[0], 13);
	insertAtFront(&arrLists[0], 25);
	insertAtFront(&arrLists[1], 8);
	insertAtFront(&arrLists[1], 9);
	insertAtFront(&arrLists[1], 13);
	insertAtFront(&arrLists[1], 64);
	insertAtFront(&arrLists[2], 8);
	insertAtFront(&arrLists[2], 17);
	insertAtFront(&arrLists[3], -2);
	insertAtFront(&arrLists[3], 0);
	insertAtFront(&arrLists[3], 4);
	insertAtFront(&arrLists[3], 8);
	insertAtFront(&arrLists[3], 11);
	insertAtFront(&arrLists[3], 16);
	insertAtFront(&arrLists[3], 18);
	insertAtFront(&arrLists[4], 4);
	insertAtFront(&arrLists[4], 21);

	printf("Initial List Configuration***\n\n");
	for (int i = 0; i < 5; i++) {
	
		printf("List %d\n", i);
		printList(arrLists[i]);
	}
	mergeLists(arrLists, 5);
	system("pause");
	system("cls");


}