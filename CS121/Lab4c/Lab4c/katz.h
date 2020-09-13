//Header file for Lab 4 Part 3
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

//scans the file and gets the next integer
int getNumber(FILE * infile);

//returns 1 if test is smaller than or equal to a, b, c, d; else returns 0
int isSmallest(int test, int a, int b, int c, int d);

//returns 1 if test is larger than or equal to a, b, c, d; else returns 0
int isLargest(int test, int a, int b, int c, int d);

//returns average of 5 ints, as a double
double takeAverage(int a, int b, int c, int d, int e);