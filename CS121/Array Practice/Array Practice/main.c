/*
* Aerie, CS121
* Instructor: Reynx <3
* Array Practice/Re-familiarization Project
* 23 June 2020
*/

#include "kumbuquet.h"

int main() {
	
	int inputArray[ARRAYSIZE] = { 0 };
	
	//opens infile for reading
	FILE * infile = NULL;
	infile = fopen("input.dat", "r");

	readArray(infile, inputArray, ARRAYSIZE);
	printArray(inputArray, ARRAYSIZE);

	reverseArray(inputArray, ARRAYSIZE);

	selectionSort(inputArray, ARRAYSIZE);
	printArray(inputArray, ARRAYSIZE);

	int inputVal = 0;
	printf("Pick a value to search for in the above array.\n");
	scanf("%d", &inputVal);
	sequentialSearch(inputVal, inputArray, ARRAYSIZE);

	printf("Binary search test.\n\n");
	binarySearchWrapper(inputArray, ARRAYSIZE);

	printf("Now for task 8.2... rand value array generation test.\n\n");
	int valueArray[VALUEARRAYSIZE] = { 0 };
	int freqArray[FREQARRAYSIZE] = { 0 };
	generateValues(valueArray, VALUEARRAYSIZE, freqArray, FREQARRAYSIZE);

	//end of program cleanup
	fclose(infile);
	EoPCleanup();
	return 0;
}