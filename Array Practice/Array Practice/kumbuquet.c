//source file for array project

#include "kumbuquet.h"

//cleanup shit at end of program, written into wrapper
void EoPCleanup(void) {
	printf("End of program, press Enter to continue.\n");
	char tempCharr = '\0';
	scanf("%c", &tempCharr);
	scanf("%c", &tempCharr);
}

//does what it says... prints out the elements of the
//target integer array of size targetSize to the console
void printArray(int target[], int targetSize) {
	printf("Target array composition is:\n{ ");
	for (int i = 0; i < targetSize; i++) {
		printf("%d ", target[i]);
	}
	printf("}\n\n");
}

//reads integer elements from infile and writes them
//sequentially into the elements of target array;
//targetSize of array must be known beforehand
//if infile contains more elements than targetSize, the last
//n - targetSize elements of infile will not be written to array!
void readArray(FILE * infile, int target[], int targetSize) {
	int nextInt = 0;
	for (int i = 0; (i < targetSize) && (!feof(infile)); i++) {
		fscanf(infile, "%d", &nextInt);
		target[i] = nextInt;
	}
}

//finds the array index of the minimum value in an int array
//between startIndex and endIndex
//and returns said index
//required for:  selectionSort
int findMinValueIndex(int target[], int startIndex, int endIndex) {
	//sets minimum value and minimum value index flag to the starting index by default
	int minVal = target[startIndex];
	int minValIndex = startIndex;
	for (int i = startIndex; i <= endIndex; i++) {
		//if specific index value is less than current minVal
		//then update the minimum value and minimum value index flag to that index
		if (minVal > target[i]) {
			minVal = target[i];
			minValIndex = i;
		}
	}
	return minValIndex;
}

//selection sort implementation for target array of size targetSize
//dependencies:  findMinValueIndex
void selectionSort(int target[], int targetSize) {
	int tempInt = 0;
	int j = 0;
	printf("Sorting target array using selection sort algorithm...\n");
	//i < targetSize - 1, because target[targetSize-2] is the second to last element
	//in the array... and if everything is in the correct spot up to and including the
	//second to last element, then the last element also has to be in the right spot
	//tldr: saves like, one trivial loop operation
	for (int i = 0; i < targetSize - 1; i++) {
		//j is the index in the portion of array from i to targetSize - 1
		//corresponding to the minimum value
		j = findMinValueIndex(target, i, targetSize - 1);
		//swap the values at target[i] and target[j] if the smallest element
		//isn't already in the correct position at the i-th spot
		if (i != j) {
			tempInt = target[i];
			target[i] = target[j];
			target[j] = tempInt;
		}
	}
	printf("Array sorted.\n\n");
}

//sequentially searches SORTED target array of targetSize for inputVal
//returns the first location(index) of the array where targetVal was found
//returns -1 if targetVal was not found
int sequentialSearch(int inputVal, int target[], int targetSize) {
	//if no matches are found then
	//targetIndex will default to -1 as required
	int targetIndex = -1;

	printf("Searching array for input value of %d.\n\n", inputVal);
	//if array is sorted, then there is no reason to check anymore if the
	//curent target[i] value is greater than the value we're searching for
	for (int i = 0; (i < targetSize) && (target[i] <= inputVal); i++) {
		if (target[i] == inputVal) {
			targetIndex = i;
		}
	}

	if (targetIndex >= 0) {
		printf("Input value of %d was found at index %d.\n\n", inputVal, targetIndex);
	}
	else {
		printf("Input value of %d was not found in array.\n\n", inputVal);
	}
	return targetIndex;
}

//searches target SORTED array of targetSize for inputVal using binary search algorithm
//returns the first location(index) of the array where targetVal was found
//returns -1 if targetVal was not found
//required for:  binarySearchWrapper
int binarySearch(int inputVal, int target[], int targetSize, int leftBound, int rightBound) {
	int targetIndex = -1;
	int splitLocation = 0;
	//when the target subarray is still greater than size one
	if (leftBound < rightBound) {
		//we want this integer division b/c splitLocation needs to be a valid index
		splitLocation = leftBound + (rightBound - leftBound) / 2;
		//check value at splitLocation index... it could be the value we're looking for
		if (inputVal == target[splitLocation]) {
			targetIndex = splitLocation;
		}
		//if inputVal is less than the value at splitLocation, search left portion of array
		else if (inputVal < target[splitLocation]) {
			targetIndex = binarySearch(inputVal, target, splitLocation - leftBound + 1, leftBound, splitLocation);
		}
		//if inputVal is greater than value at splitLocation, search right portion of array
		else if (inputVal > target[splitLocation]) {
			targetIndex = binarySearch(inputVal, target, rightBound - splitLocation + 1, splitLocation + 1, rightBound);
		}
		//catches weird errors, hopefully will never run
		else
		{
			printf("Your binary search function fucked up... check your goddamn code.\n\n");
		}
	}
	//if the target subarray is size 1
	else if (leftBound == rightBound) {
		//if the value of this element matches our input, return the index of this element
		//otherwise, do nothing
		if (target[leftBound] == inputVal) {
			targetIndex = leftBound;
			return targetIndex;
		}
	}
	//catches errors
	else {
		printf("Your binary search function fucked up... check your goddamn code.\n\n");
	}

	//if after all the stuff above targetIndex hasn't been modified,
	//it will remain as -1 which will mean the inputVal wasn't found.	
	return targetIndex;
}

//binary search wrapper with user prompting and all the fancy goodies
//dependencies:  binarySearch (duh?), printArray
void binarySearchWrapper(int target[], int targetSize) {
	
	int inputVal = 0;
	int targetIndex = 0;
	printf("Cheater mode!  Here's the array you're \"searching\"...\n\n");
	printArray(target, targetSize);
	printf("Enter a value to search for:\n");
	scanf("%d", &inputVal);
	printf("I am searching the array.\n\n");

	targetIndex = binarySearch(inputVal, target, targetSize, 0, targetSize - 1);
	if (targetIndex == -1) {
		printf("Your input value of %d was not found.\n\n", inputVal);
	}
	else {
		printf("Your input value of %d was found in the array at location %d.\n\n", inputVal, targetIndex);
	}
}

//reverses contents of target int array of size targetSize.
//requires:  printArray
void reverseArray(int target[], int targetSize) {
	printf("Reversing array...\n\n");
	//integer division forces midPoint to be just before the middle element for an array
	//with an even number of elements, e.g. ( _ _ * _ _ _)
	//or to be the middle element for an array
	//with an odd number of elements, e.g. ( _ _ * _ _ )
	//either scenario is fine for us.
	int midPoint = targetSize / 2;
	//variable to be a temporary container for the swap.
	int swap = 0;
	for (int i = 0; i <= midPoint; i++)
	{
		swap = target[i];
		target[i] = target[(targetSize - 1) - i];
		target[(targetSize - 1) - i] = swap;
	}
	printArray(target, targetSize);
}

//generates random values into valArray and then updates the frequency of each value into freqArray
//requires: stdlib.h for rand function, printArray
void generateValues(int valArray[], int valArraySize, int freqArray[], int freqArraySize) {
	printf("Generating %d values between 0 and %d and populating array...\n\n", valArraySize, freqArraySize - 1);
	int nextRandVal = 0;
	for (int i = 0; i < valArraySize; i++) {
		//generate a value from 0 to freqArraySize - 1 and put it into the ith cell
		nextRandVal = rand() % freqArraySize;
		//update freqArray
		valArray[i] = nextRandVal;
		freqArray[nextRandVal]++;
	}
	printf("Random values array:\n\n");
	printArray(valArray, valArraySize);
	printf("Frequency array:\n\n");
	printArray(freqArray, freqArraySize);
}