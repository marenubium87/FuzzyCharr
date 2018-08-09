//Source file for Lab 8a
//Stains easily; do not jizz on

#include "warningdontjizzonthis.h"

//debug/test function; prints out all of the values of target integer array onto the console
//precondition:  target array and size in elements of target array need to be available
//postcondition:  target array is printed out in { 0 1 2 3 4 5 ... } format
void printArray(int target[], int targetSize)
{
	printf("Target array composition is:\n");
	printf("{ ");
	for (int i = 0; i < targetSize; i++)
	{
		printf("%d ", target[i]);
	}
	printf("}");
}

//populates an integer array from an input file
//prec:		infile must be open for reading
//			infile must contain all integers
//			number of integers in infile must equal target array size
void populateArray(FILE * infile, int target[], int targetSize)
{
	int tempVal = 0;
	for (int i = 0; i < targetSize; i++)
	{
		//read next integer from infile and save to tempVal
		fscanf(infile, "%d", &tempVal);
		//pop it into the i-th location in array
		target[i] = tempVal;
	}
}

//reverses all of the elements of an integer array of size targetSize
void reverseArray(int target[], int targetSize)
{
	//we *want* this integer division/truncation
	//because for an array with an odd number of elements,
	//this will return the number of elements before the one in the exact middle
	//which doesn't need to be swapped anyway.
	//for an even number of elements there is no issue.
	int halfArray = targetSize / 2;

	int tempVal = 0;
	//this loop essentially swaps the first value with the last, the second with the second last, etc.
	for (int i = 0; i < halfArray; i++)
	{
		//store i-th element temporarily
		tempVal = target[i];
		//place the corresponding element on the other side of the midpoint of the array into the i-th slot
		target[i] = target[(targetSize - 1) - i];
		//finally, place the temporarily stored i-th element of the array into the corresponding location
		//on the other side of the midpoint of the array
		target[(targetSize - 1) - i] = tempVal;
	}
}