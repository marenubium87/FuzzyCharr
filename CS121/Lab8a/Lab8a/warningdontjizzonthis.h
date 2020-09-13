//Header file for Lab 8a
//Stains easily; do not jizz on

#define _CRT_SECURE_NO_WARNINGS
#define ARRAYSIZE 9

#include <stdio.h>

//test function; prints out all of the values of target integer array onto the console
//precondition:  target array and size in elements of target array need to be available
//postcondition:  target array is printed out in { 0 1 2 3 4 5 ... } format
void printArray(int target[], int targetSize);

//populates an integer array from an input file
//prec:		infile must be open for reading
//			infile must contain all integers
//			number of integers in infile must equal target array size
void populateArray(FILE * infile, int target[], int targetSize);

//reverses all of the elements of an integer array of size targetSize
void reverseArray(int target[], int targetSize);