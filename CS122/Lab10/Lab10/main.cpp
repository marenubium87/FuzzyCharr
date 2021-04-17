//lab 10 merge sort

#include "lab10.h"

int main() {
	int myArr[ARR_SIZE] = { 3, -5, 8, -1, 2, -6, 11, 5, 9, 0, -3, 1, 4, 7, 6, -2 };

	mergeSort(myArr, 0, ARR_SIZE - 1);

	int degenerateArray[1] = { 5 };
	mergeSort(degenerateArray, 0, 0);

	int smallArray[2] = { 3, 8 };
	mergeSort(smallArray, 0, 1);

	return 0;
}