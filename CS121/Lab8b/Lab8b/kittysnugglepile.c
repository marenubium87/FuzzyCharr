//The (very very soft) source file for lab 8b

#include "kittysnugglepile.h"

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

//debug/test function; prints out all of the values of target integer array to outfile
//precondition:		*target array and size in elements of target array need to be available
//					*outfile must be open for writing
//postcondition:  target array is printed out to file in { 0 1 2 3 4 5 ... } format
void printArrayFile(int target[], int targetSize, FILE * outfile)
{
	fprintf(outfile, "Target array composition is:\n");
	fprintf(outfile, "{ ");
	for (int i = 0; i < targetSize; i++)
	{
		fprintf(outfile, "%d ", target[i]);
	}
	fprintf(outfile, "}");
}

//seeds an integer array of size targetSize with integers btwn ONE (NOT ZERO!) and randMax
void seedArray(int target[], int targetSize, int randMax)
{
	for (int i = 0; i < targetSize; i++)
	{
		target[i] = (rand() % randMax) + 1;
	}
}

/*	for an integer array target with size targetSize, fills countArray with integers representing
	the number of times an integer i has occurred in target array into the corresponding index i element
	of countArray

	...in other words, if 21 occurred twice in target array, then countArray[21] = 2

	prec:	countArray must have size MAXRAND + 1 and be initialized to all zeroes
			(MAXRAND + 1 is so that if we're generating numbers from, say, 1 to 30, then
			countArray must have 31 elements so that countArray[30] exists)
*/
void countIntsArray(int target[], int targetSize, int countArray[], int countArraySize)
{
	if (countArraySize != MAXRAND + 1)
	{
		printf("Error: countArray does not have the proper size; aborting.\n\n");
	}
	else
	{
		//initializing counter variable
		int i = 0;
		//initializing temp value to read from target array and increment into countArray
		int tempVal = 0;

		for (i = 0; i < targetSize; i++)
		{
			tempVal = target[i];
			countArray[tempVal] += 1;
		}
	}
}

/*	prints out the values for each element [i] in countArray to outfile in the format:

Number	Count
1:		0
2:		0
3:		1
etc.

Note that this function assumes that you've generated numbers from 1 to MAXRAND and thus
will not print out the 0th element in countArray.
*/
void printCountsFile(int countArray[], int countArraySize, FILE * outfile)
{
	fprintf(outfile, "Number\tCount\n");
	for (int i = 1; i < countArraySize; i++)
	{
		fprintf(outfile, "%d\t\t%d\n", i, countArray[i]);
	}
}