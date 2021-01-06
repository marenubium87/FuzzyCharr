//source for stack testing functions

#include "testStack.h"

//aux function for testing
//clears targetStack's contents and frees memory
void deleteStack(StackNode ** targetStack) {
	//repeatedly deletes and frees first element
	//until no elements remain
	StackNode * pCurr = NULL;
	while (*targetStack != NULL) {
		pCurr = *targetStack;
		*targetStack = (*targetStack)->pNext;
		free(pCurr);
	}
}

//test function for stack push
//returns TRUE if all tests passed, FALSE else
int testPush() {
	printf("Testing push...\n");
	int numTestsFailed = 0;
	StackNode * testStack = NULL;
	const double n1 = 420.69;
	const double n2 = 666.666;
	const double n3 = 2021.0105;
	
	printf("  -pushing onto empty stack...   ");
	push(n1, &testStack);

	if (testStack->data == n1 &&
			testStack->pNext == NULL) {
		printf("PASSED\n");
	}
	else {
		printf("FAILED\n");
		numTestsFailed++;
	}

	printf("  -pushing onto stack with one element...   ");
	push(n2, &testStack);

	StackNode * pCurr = testStack;
	if (pCurr->data == n2) {
		pCurr = pCurr->pNext;
	}
	if (pCurr->data == n1 &&
		pCurr->pNext == NULL) {
		printf("PASSED\n");
	}
	else {
		printf("FAILED\n");
		numTestsFailed++;
	}

	printf("  -pushing onto stack with multiple elements...   ");
	push(n3, &testStack);
	pCurr = testStack;
	if (pCurr->data == n3) {
		pCurr = pCurr->pNext;
	}
	if (pCurr->data == n2) {
		pCurr = pCurr->pNext;
	}
	if (pCurr->data == n1 &&
		pCurr->pNext == NULL) {
		printf("PASSED\n");
	}
	else {
		printf("FAILED\n");
		numTestsFailed++;
	}

	//clear memory
	deleteStack(&testStack);

	if (numTestsFailed == 0) {
		printf("ALL push TESTS PASSED****\n\n");
		return TRUE;
	}
	else {
		printf("push TESTS FAILED!!\n\n");
		return FALSE;
	}
}

//test function for isEmpty
//returns TRUE if tests passed, FALSE else
//requires push function to work, so test after that
int testIsEmpty() {
	printf("Testing isEmpty...\n");

	StackNode * testStack = NULL;
	int numTestsFailed = 0;
	
	printf("  -testing when stack is empty...   ");
	if (isEmpty(testStack)) {
		printf("PASSED\n");
	}
	else {
		printf("FAILED\n");
		numTestsFailed++;
	}

	printf("  -testing when stack is not empty...   ");
	push(1701.5, &testStack);
	if (!isEmpty(testStack)) {
		printf("PASSED\n");
	}
	else {
		printf("FAILED\n");
		numTestsFailed++;
	}

	//clear memory
	deleteStack(&testStack);

	if (numTestsFailed == 0) {
		printf("ALL isEmpty TESTS PASSED****\n\n");
		return TRUE;
	}
	else {
		printf("isEmpty TESTS FAILED!!\n\n");
		return FALSE;
	}
}

//test function for stack pop
//returns TRUE if all tests passed, FALSE else
//requires push and isEmpty functions to work, so test after those
int testPop() {
	printf("Testing pop...\n");
	int numTestsFailed = 0;
	StackNode * testStack = NULL;
	StackNode * pCurr = NULL;
	const double n1 = 123.45;
	const double n2 = 138.57;
	const double n3 = 269.896;
	push(n1, &testStack);
	push(n2, &testStack);
	push(n3, &testStack);

	pop(&testStack);
	pCurr = testStack;
	printf("  -pop test 1 of 3...  ");
	if (pCurr->data == n2) {
		pCurr = pCurr->pNext;
	}
	if (pCurr->data == n1) {
		pCurr = pCurr->pNext;
	}
	if (pCurr == NULL) {
		printf("PASSED\n");
	}
	else {
		printf("FAILED\n");
		numTestsFailed++;
	}

	pop(&testStack);
	printf("  -pop test 2 of 3...  ");
	pCurr = testStack;
	if (pCurr->data == n1) {
		pCurr = pCurr->pNext;
	}
	if (pCurr == NULL) {
		printf("PASSED\n");
	}
	else {
		printf("FAILED\n");
		numTestsFailed++;
	}

	pop(&testStack);
	printf("  -pop test 3 of 3...  ");
	if(testStack == NULL) {
		printf("PASSED\n");
	}
	else {
		printf("FAILED\n");
		numTestsFailed++;
	}

	//clear memory
	deleteStack(&testStack);

	if (numTestsFailed == 0) {
		printf("ALL pop TESTS PASSED****\n\n");
		return TRUE;
	}
	else {
		printf("pop TESTS FAILED!!\n\n");
		return FALSE;
	}
}

//test function for peek
//returns TRUE if tests passed, FALSE else
//requires all previous tests to work, so test after those
int testPeek() {
	printf("Testing peek...\n");
	int numTestsFailed = 0;
	StackNode * testStack = NULL;

	double const n1 = 167.78;
	double const n2 = 357.9;
	
	printf("  -test 1 of 3...  ");
	push(n1, &testStack);
	if (peek(testStack) == n1) {
		printf("PASSED\n");
	}
	else {
		printf("FAILED\n");
		numTestsFailed++;
	}

	printf("  -test 2 of 3...  ");
	push(n2, &testStack);
	if (peek(testStack) == n2) {
		printf("PASSED\n");
	}
	else {
		printf("FAILED\n");
		numTestsFailed++;
	}

	printf("  -test 3 of 3...  ");
	pop(&testStack);
	if (peek(testStack) == n1) {
		printf("PASSED\n");
	}
	else {
		printf("FAILED\n");
		numTestsFailed++;
	}

	//clear memory
	deleteStack(&testStack);

	if (numTestsFailed == 0) {
		printf("ALL peek TESTS PASSED****\n\n");
		return TRUE;
	}
	else {
		printf("peek TESTS FAILED!!\n\n");
		return FALSE;
	}
}

//wrapper to conduct all tests
void testWrapper() {
	testPush();
	testIsEmpty();
	testPop();
	testPeek();
}