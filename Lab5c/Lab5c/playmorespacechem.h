//Header file for Lab 5 Part 3

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
//can't include meth, so i'll settle for this
#include <math.h>

//opens input.txt for READ
FILE * openInput(void);

//opens output.txt for WRITE
FILE * openOutput(void);

//reads the next int from infile
int readNextNumber(FILE * infile);

//finds the GCD of a and b and returns as int
int greatest_common_divisor(int a, int b);

//writes the line "The GCD is: #" to outfile, where # is the passed-in number
void writeGCD(FILE * outfile, int gcd);