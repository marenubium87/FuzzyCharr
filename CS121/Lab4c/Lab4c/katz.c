//Source File for Lab 4 Part 3

//grab header file
#include "katz.h"

//scans file and gets next integer
int getNumber(FILE * infile)
{
	int number = 0;
	fscanf(infile, "%d", &number);
	return number;
}

//returns 1 if test is smaller than or equal to a, b, c, d; else returns 0
int isSmallest(int test, int a, int b, int c, int d)
{
	int isSmallest = 0;
	if (test <= a && test <= b && test <= c && test <= d)
	{
		isSmallest = 1;
	}
	return isSmallest;
}

//returns 1 if test is larger than or equal to a, b, c, d; else returns 0
int isLargest(int test, int a, int b, int c, int d)
{
	int isLargest = 0;
	if (test >= a && test >= b && test >= c && test >= d)
	{
		isLargest = 1;
	}
	return isLargest;
}

//returns the average of the 5 numbers (ints) as a double
double takeAverage(int a, int b, int c, int d, int e)
{
	double average = 0.0;

	average = (a + b + c + d + e) / (double)5;
	return average;
}