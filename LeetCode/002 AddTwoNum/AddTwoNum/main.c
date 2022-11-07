#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <Windows.h>

struct ListNode {
	int val;
	struct ListNode *next;
 };
 
void printList(struct ListNode * pListHead) {
	while (pListHead != NULL) {
		printf("%d", pListHead->val);
		pListHead = pListHead->next;
	}
	printf("\n");
}

struct ListNode * makeNode(int val) {
	struct ListNode * pMem = (struct ListNode *)malloc(sizeof(struct ListNode));
	pMem->val = val;
	pMem->next = NULL;
	return pMem;
}

void addToTail(struct ListNode ** pList, int val) {
	struct ListNode * pMem = makeNode(val);
	if (*pList == NULL) {
		*pList = pMem;
	}
	else {
		//traverse list
		struct ListNode * pCurr = *pList;
		while (pCurr->next != NULL) {
			pCurr = pCurr->next;
		}
		pCurr->next = pMem;
	}
}

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {

	//create answer list
	struct ListNode * pAnswerHead = NULL;
	struct ListNode * pCurr = NULL;

	int carry = 0;

	//while at least one list still has digits remaining or carry isn't zero
	while (l1 != NULL || l2 != NULL || carry > 0) {
		struct ListNode * tempNode = (struct ListNode*)malloc(sizeof(struct ListNode));
		tempNode->val = 0;
		tempNode->val += carry;
		if (l1 != NULL) {
			tempNode->val += l1->val;
			l1 = l1->next;
		}
		if (l2 != NULL) {
			tempNode->val += l2->val;
			l2 = l2->next;
		}
		tempNode->next = NULL;
		carry = 0;
		if (tempNode->val >= 10) {
			tempNode->val -= 10;
			carry++;
		}

		//attach tempNode to end of list
		if (pAnswerHead == NULL) {
			pAnswerHead = tempNode;
			pCurr = pAnswerHead;
		}
		else {
			pCurr->next = tempNode;
			pCurr = pCurr->next;
		}
	}
	return pAnswerHead;
}

int main() {

	struct ListNode * l1 = NULL;
	struct ListNode * l2 = NULL;
	struct ListNode * l3 = NULL;
	addToTail(&l1, 5);
	printList(l1);
	addToTail(&l2, 5);
	printList(l2);
	l3 = addTwoNumbers(l1, l2);
	printList(l3);
	system("pause");
	return 0;
}