//Header file for Lab 5a

#define _CRT_SECURE_NO_WARNINGS
//number of payments in file
#define NUMPAYMENTS 4
//low and medium income cutoffs
#define LOW 15000
#define MED 200000

#include <stdio.h>

//opens salaries.txt for READING
FILE * openInputFile(void);

//reads next number from infile
int readNextNumber(FILE * infile);

//loops through NUMPAYMENTS times to gather salary data
//and +=s to get total salary
int computeMoneyz(FILE * infile);

//judges people based on their salary
void passJudgment(int salary);