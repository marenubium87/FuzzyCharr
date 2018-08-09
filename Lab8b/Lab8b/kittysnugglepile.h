//The (admittedly very soft) header file for lab 8b

#define _CRT_SECURE_NO_WARNINGS
//we're going to be generating random numbers between 1 and this number
#define MAXRAND 100

#include <stdio.h>
//required for rand operations
#include <stdlib.h>
//required for seeding rand... okay I mean, not... required, but... yeah.  okay.
#include <time.h>

//debug/test function; prints out all of the values of target integer array onto the console
//precondition:  target array and size in elements of target array need to be available
//postcondition:  target array is printed out in { 0 1 2 3 4 5 ... } format
void printArray(int target[], int targetSize);

//debug/test function; prints out all of the values of target integer array to outfile
//precondition:		*target array and size in elements of target array need to be available
//					*outfile must be open for writing
//postcondition:  target array is printed out to file in { 0 1 2 3 4 5 ... } format
void printArrayFile(int target[], int targetSize, FILE * outfile);

//seeds an integer array of size targetSize with integers btwn ONE (NOT ZERO!) and randMax
void seedArray(int target[], int targetSize, int randMax);

/*	for an integer array target with size targetSize, fills countArray with integers representing
	the number of times an integer i has occurred in target array into the corresponding index i element
	of countArray

	check function in source file for more documentation
*/
void countIntsArray(int target[], int targetSize, int countArray[], int countArraySize);

/*	prints out the values for each element [i] in countArray to outfile in the format:
	
	Number	Count
	1:		0
	2:		0
	3:		1
	etc.

	Note that this function assumes that you've generated numbers from 1 to MAXRAND and thus
	will not print out the 0th element in countArray.
*/
void printCountsFile(int countArray[], int countArraySize, FILE * outfile);