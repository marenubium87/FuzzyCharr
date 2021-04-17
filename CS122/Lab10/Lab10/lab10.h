//header for lab 10

#define ARR_SIZE 16

#include <iostream>

using std::cin;
using std::cout;
using std::string;
using std::endl;

//mergeSort implementation
//pass in 0, arraySize - 1 for left and right respectively
void mergeSort(int arr[], int left, int right);

//helper called by mergeSort
void sort(int arr[], int tempArr[], int left, int right);

//merges two subarrays left and right, where leftStart and rightStart
//are start indices for subarrays in arr[], and leftLength and rightLength
//are number of elements each subarray contains.
//builds the correct merged array in tempArr and then pastes it back
//in the correct location in the original array.
void merge(int arr[], int tempArr[],
	int leftStart, int leftLength,
	int rightStart, int rightLength);