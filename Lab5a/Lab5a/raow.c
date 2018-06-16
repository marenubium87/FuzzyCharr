//Source file for Lab 5 Part 1

#include "raow.h"

//opens salaries.txt for READING
FILE * openInputFile(void)
{
	FILE * infile = NULL;
	infile = fopen("salaries.txt", "r");
	return infile;
}

//i mean, it does what it says on the tin...
//infile must be open for reading
int readNextNumber(FILE * infile)
{
	int nextInt = 0;
	fscanf(infile, "%d", &nextInt);
	return nextInt;
}

//loops through NUMPAYMENTS times to gather salary data
//and += to moneyz to compute total salary
//infile must be open for reading
//dependencies:  readNextNumber
int computeMoneyz(FILE * infile)
{
	int moneyz = 0;
	for (int count = 0; count <= NUMPAYMENTS; count++)
	{
		moneyz += readNextNumber(infile);
	}
	return moneyz;
}

//passes judgment on people based on their salary
void passJudgment(int salary)
{
	if (salary <= LOW)
	{
		printf("Low income - gotta make more moneyz.\n");
	}
	else if (salary <= MED)
	{
		printf("Medium income - c'mon, you can do better.\n");
	}
	else
	{
		printf("High income - good work; keep subjugating the 99%%!\n");
	}
}