//Header file for Lab 5 Part 2

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

//opens data.txt for reading
FILE * openInputFile(void);

//opens output.txt for writing
FILE * openOutputFile(void);

//reads next (double) value from infile and returns it
double readMahValue(FILE * infile);

//takes the average of all elements of infile
double takeMahAverage(FILE * infile);

//writes average to outfile
void writeMahAverage(FILE * outfile, double average);