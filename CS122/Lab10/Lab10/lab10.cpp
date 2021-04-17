//source for lab 10

#include "lab10.h"

//mergeSort implementation
//pass in 0, arraySize - 1 for left and right respectively
void mergeSort(int arr[], int left, int right) {
	
	//we don't sort size one arrays in this household
	if (right - left < 1) {
		return;
	}

	int tempArr[ARR_SIZE];
	sort(arr, tempArr, left, right);
}

//recursive helper called by mergeSort
void sort(int arr[], int tempArr[], int left, int right) {
	if (left == right) {
		return;
	}
	else {
		//splitting into...
		//...left side
		sort(arr, tempArr, left, (left + right) / 2);
		//...right side
		sort(arr, tempArr, (left + right) / 2 + 1, right);

		//length of subarray is right - left + 1, in general.
		merge(arr, tempArr, left, (left + right) / 2 - left + 1,
			(left + right) / 2 + 1, right - (left + right) / 2 - 1 + 1);
	}
}

//merges two subarrays left and right, where leftStart and rightStart
//are start indices for subarrays in arr[], and leftLength and rightLength
//are number of elements each subarray contains.
//builds the correct merged array in tempArr and then pastes it back
//in the correct location in the original array, so that the constructed
//subarray can be used again in the next call, if applicable.
void merge(int arr[], int tempArr[],
	int leftStart, int leftLength,
	int rightStart, int rightLength) {
	int i = leftStart;
	int j = rightStart;

	//tempArray's index
	int k = leftStart;

	//while both arrays not at end yet
	while (i < leftStart + leftLength && j < rightStart + rightLength) {
		//compare elements at those indices
		if (arr[i] >= arr[j]) {
			tempArr[k] = arr[i];
			i++;
		}
		else {
			tempArr[k] = arr[j];
			j++;
		}
		k++;
	}

	//one of the arrays is exhausted now, but which one?
	if (!(j < rightStart + rightLength)) {
		//if unexhausted array is i
		while (i < leftStart + leftLength) {
			tempArr[k] = arr[i];
			i++;
			k++;
		}
	}
	else if (!(i < leftStart + leftLength)) {
		//if unexhausted array is j
		while (j < rightStart + rightLength) {
			tempArr[k] = arr[j];
			j++;
			k++;
		}
	}

	//both lists should be exhausted now, need to paste over the subarray
	//back into the main array in the correct location
	for (k = leftStart; k < leftStart + leftLength + rightLength; k++) {
		arr[k] = tempArr[k];
	}
}