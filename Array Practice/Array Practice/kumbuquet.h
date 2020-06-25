//header file for array project

#define _CRT_SECURE_NO_WARNINGS
#define ARRAYSIZE 10
#define VALUEARRAYSIZE 20
#define FREQARRAYSIZE 10

#include <stdio.h>
#include <stdlib.h>

//cleanup shit at end of program, written into wrapper
void EoPCleanup(void);

//does what it says... prints out the elements of the
//target integer array of size targetSize to the console
void printArray(int target[], int targetSize);

//reads integer elements from infile and writes them
//sequentially into the elements of target array;
//targetSize of array must be known beforehand
//if infile contains more elements than targetSize, the last
//n - targetSize elements of infile will not be written to array!
void readArray(FILE * infile, int target[], int targetSize);

//finds the array index of the minimum value in an int array
//between startIndex and endIndex
//and returns said index
//required for:  selectionSort
int findMinValueIndex(int target[], int startIndex, int endIndex);

//selection sort implementation for target array of size targetSize
//dependencies:  findMinValueIndex
void selectionSort(int target[], int targetSize);

//sequentially searches SORTED target array of targetSize for inputVal
//returns the first location(index) of the array where targetVal was found
//returns -1 if targetVal was not found
int sequentialSearch(int inputVal, int target[], int targetSize);

//searches target SORTED array of targetSize for inputVal using binary search algorithm
//returns the first location(index) of the array where targetVal was found
//returns -1 if targetVal was not found
//required for:  binarySearchWrapper
int binarySearch(int inputVal, int target[], int targetSize, int leftBound, int rightBound);

//binary search wrapper with user prompting and all the fancy goodies
//dependencies:  binarySearch (duh?), printArray
void binarySearchWrapper(int target[], int targetSize);

//reverses contents of target int array of size targetSize.
//requires:  printArray
void reverseArray(int target[], int targetSize);

//generates random values into valArray and then updates the frequency of each value into freqArray
//requires: stdlib.h for rand function
void generateValues(int valArray[], int valArraySize, int freqArray[], int freqArraySize);