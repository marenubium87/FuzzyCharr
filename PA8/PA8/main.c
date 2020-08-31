/*
* Aerie, CS121
* Instructor: Reynx <3
* PA8
* 21 Aug 2020
*/

#include "lastjokethisclass.h"

int main() {
	
	////task 1
	printf(" ** Task 1\n\n");
	char sorc[60] = "";
	char dest[60] = "";
	int n = 0;
	int len = 0;
	printf("Enter a string for source: ");
	fgets(sorc, 59, stdin);
	//trims the annoying new line char that arises when
	//using fgets.
	len = strlen(sorc);
	if (sorc[len - 1] == '\n');
	{
		sorc[len - 1] = '\0';
	}
	printf("\n");
	printf("Enter a string for dest: ");
	fgets(dest, 59, stdin);
	//trims the annoying new line char that arises when
	//using fgets.
	len = strlen(dest);
	if (dest[len - 1] == '\n');
	{
		dest[len - 1] = '\0';
	}
	printf("\n");
	printf("Enter max # of chars to copy from source to dest:  ");
	scanf("%d", &n);
	my_str_n_cat(sorc, dest, n);
	system("pause");

	////task 2
	printf(" ** Task 2\n\n");
	char * stringsArray[] = {
		"asshole",
		"sweetly",
		"ravage",
		"i shall",
		"verily",
		"an",
	};
	printf("Unsorted array:\n\n");
	printStringArray(stringsArray, 6);
	printf("Sorted array:\n\n");
	bubble_sort(stringsArray, 6);
	printStringArray(stringsArray, 6);
	system("pause");

	//task 3
	printf(" ** Task 3\n\n");
	int input = 0;
	printf("Enter a positive int > 2:  ");
	scanf("%d", &input);
	int primeSum = sum_primes(input);
	printf("\nSum of primes from 2 to %d is:  %d\n\n", input, primeSum);
	system("pause");

	//task 4
	printf(" ** Task 4\n\n");
	int testArray1[10] = { 8, 5, -1, 4, -6, 37, -4, 1, -5, 24 };
	//case with all numbers > 0
	int testArray2[10] = { 8, 5, 3, 4, 6, 1, 4, 7, 8 , 10 };
	int testArray3[10] = { 4, 6, -4, -4, 2, 5, -3, -7, 99, -66 };
	//edge cases with arrays of size 1
	int testArray4[1] = { 3 };
	int testArray5[1] = { 0 };
	int testArray6[1] = { -4 };

	smallest_sum_sequence(testArray1, 10);
	smallest_sum_sequence(testArray2, 10);
	smallest_sum_sequence(testArray3, 10);
	smallest_sum_sequence(testArray4, 1);
	smallest_sum_sequence(testArray5, 1);
	smallest_sum_sequence(testArray6, 1);
	system("pause");
	
	//task 5
	printf(" ** Task 5\n\n");
	//set up 2d int array
	int task5Array[ROWS][COLS] = {
		{ 5, 2, 2, -3, 8 },
		{ 1, 3, -8, -8, 9 },
		{ 9, 9, 9, 6, 5 },
		{ 3, -1, -1, -1, -1 },
		{ -1, -6, 5, 3, 8 },
	};
	print2DArray(task5Array, ROWS, COLS);
	
	//setting up this pointer to a pointer bullshit
	int address = 0;
	int * pAddress = &address;
	//heheh, pp
	int ** ppAddress = &pAddress;
	//setting pointer for max sequence
	int maxSeq = 0;
	int * pMaxSeq = &maxSeq;

	printf("Column addresses:\n");
	printf("%d\n", &task5Array[0][0]);
	printf("%d\n", &task5Array[1][0]);
	printf("%d\n", &task5Array[2][0]);
	printf("%d\n", &task5Array[3][0]);
	printf("%d\n", &task5Array[4][0]);

	max_consecutive_integers(task5Array, ROWS, COLS, ppAddress, pMaxSeq);
	printf("Max seq is %d at address %d\n\n", *pMaxSeq, *ppAddress);
	printf("Okey bai foreva\n\n");
	system("pause");
	return 0;
}