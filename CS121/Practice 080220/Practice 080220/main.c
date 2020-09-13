#define _CRT_SECURE_NO_WARNINGS
#define NUMS_ARR_SIZE 10

#include <stdio.h>
#include <Windows.h>

//prints target int array of size targetSize to the console
void printArray(int target[], int targetSize) {
	printf("Target array composition:\n");
	printf("{ ");
	for (int i = 0; i < targetSize; i++) {
		printf("%d ", target[i]);
	}
	printf("}\n\n");
}

//binary search for target int array
//attempts to find the index of the element containing searchVal
//within the indices lBound and rBound (inclusive)
//I can recurse (shit, shit, shit...) this
//returns -1 if searchVal was not found, else returns index of
//element containing searchVal
//precondition:  target is a sorted int array
int binSearch(int target[], int lBound, int rBound,
	int searchVal) {

	int foundIndex = -1;

	//are we already at the situation where the (sub)array is of size 1?
	if (rBound == lBound) {
		if (target[lBound] == searchVal) {
			foundIndex = lBound;
		}
	}
	//so if the (sub)array is not of size 1...
	else {
		//integer division is okay... for array or sub-array with odd number
		//of elements, int division will find the middle element
		//e.g. _ _ x _ _
		//with an even number of elements, will find the first element to the
		//left of the midline of the array or subarray
		//e.g. _ _ x _ _ _
		int mid = lBound + (rBound - lBound) / 2;

		//is the mid element the searchVal?
		if (target[mid] == searchVal) {
			foundIndex = mid;
		}
		//this implies that searchVal is in the left half of the current
		//array or subarray
		else if (target[mid] > searchVal) {
			foundIndex = binSearch(target, lBound, mid,
				searchVal);
		}
		//this implies that searchVal is in the right half of the current
		//array or subarray
		else if (target[mid] < searchVal) {
			foundIndex = binSearch(target, mid + 1, rBound,
				searchVal);
		}
	}
	return foundIndex;
}

//auxiliary function
//determines whether the neighbors of currIndex in target array
//also have the same value as target[currIndex]
//returns the index of the first neighbor searched that does have
//the same value, checking left first, then right
//returns -1 if neither neighbor has the same value
//picture:  { _ ... _ c x c _ ... _}
//checks the locations marked c if currIndex is marked x
//precondition:  target is a sorted int array
int checkNeighbors(int target[], int targetSize, int currIndex) {

	int foundIndex = -1;

	//only check left neighbor if it exists, e.g. currIndex isn't 0
	if (currIndex > 0) {
		if (target[currIndex] == target[currIndex - 1]) {
			foundIndex = currIndex - 1;
			return foundIndex;
		}
	}
	//if left neighbor isn't the same value, then check right neighbor
	//but only if we're not at the far right end of the array
	if (currIndex < targetSize - 1) {
		if (target[currIndex] == target[currIndex + 1]){
			foundIndex = currIndex + 1;
			return foundIndex;
		}
	}
	return foundIndex;
}

//finds two values contained in target int array that add up to sumVal,
//and passes the indices of the two values as output params index1 and index2
//precondition:  target is a sorted int array
void twoSum(int target[], int targetSize, int sumVal,
	int * index1, int * index2) {
	int lBound = 0;
	int rBound = targetSize - 1;
	int found = -1;

	//first, can we shrink where we're searching in the array, in general?  
	//if the smallest elements are such that adding them
	//to even the largest element cannot achieve a value as large as sumVal,
	//then we can exclude them from our search.
	while (target[lBound] + target[targetSize - 1] < sumVal) {
		lBound++;
	}
	//same argument for elements that are too large
	while (target[rBound] + target[0] > sumVal) {
		rBound--;
	}
	//now that the bounds of our restricted array are set,
	//we don't want to touch lBound and rBound after this point.

	//then for each i, figure out what target[i] needs to be added to
	//to get to sumVal, and binSearch for that in the shrinked array.
	for (int i = lBound; i <= rBound; i++) {
		found = binSearch(target, lBound, rBound,
			sumVal - target[i]);
		//if what we found is the same element though, we have to
		//check the neighbors since we may not use the same element twice.
		if (found == i) {
			found = checkNeighbors(target, targetSize, i);
		}
		//at any point if we find what we're looking for, assign the correct
		//indices to both values, then stop going through loop.
		if (found != -1) {
			*index1 = i;
			*index2 = found;
			break;
		}
	}
}

int main() {
	int numsArray[NUMS_ARR_SIZE] = { 2, 3, 9, 11, 20, 20, 20, 28, 37, 45 };
	printArray(numsArray, NUMS_ARR_SIZE);
	
	int firstIndex = -1, secondIndex = -1;

	int sumVal = 20;

	twoSum(numsArray, NUMS_ARR_SIZE, sumVal, &firstIndex, &secondIndex);
	printf("Looking for two numbers that add to %d...\n", sumVal);
	if (firstIndex != -1 && secondIndex != -1) {
		printf("Found values of %d and %d at array locations %d and %d\n\n",
			numsArray[firstIndex], numsArray[secondIndex], 
			firstIndex, secondIndex);
	}
	else {
		printf("No values meeting criteria were found in array.\n\n");
	}
	
	system("pause");
	return 0;
}