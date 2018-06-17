//Source for Lab 5 Part 4

#include "runningoutofjokes.h"

//opens input.txt for READING
FILE * getInputFile(void)
{
	FILE * infile = NULL;
	infile = fopen("input.txt", "r");
	return infile;
}

//i mean, it literally does what it sounds like...
double readNextNumber(FILE * infile)
{
	double myNumbuhz = 0.0;
	fscanf(infile, "%lf", &myNumbuhz);
	//technically, myNumbuh, but myNumbuhz just sounds better.  sorry.
	return myNumbuhz;
}

//prints out highest double in infile
//infile must be open for reading
//dependencies:  readNextNumber
void printHighest(FILE * infile)
{
	double highest = 0.0;

	//make sure we be reading the first number...
	rewind(infile);
	
	//set highest to first number, else it'll create a nasty bug if all numbers in file are negative
	highest = readNextNumber(infile);
	
	int kitties = 0;
	for (kitties = 1; !feof(infile); kitties++)
	{
		double nextNum = 0.0;
		//read next number, if it's greater than the current highest, then replace, else do nothing
		nextNum = readNextNumber(infile);
		if (nextNum >= highest)
		{
			highest = nextNum;
		}
	}

	printf("Evaluated %d numbers in file.\n", kitties);
	printf("Highest number is %lf\n\n", highest);
}

//prints out lowest double in infile
//infile must be open for reading
//dependencies: readNext Number
void printLowest(FILE * infile)
{
	double lowest = 0.0;

	//make sure we be reading the first number...
	rewind(infile);

	//set highest to first number, else it'll create a nasty bug if all numbers in file are positive
	lowest = readNextNumber(infile);

	int kitties = 0;
	for (kitties = 1; !feof(infile); kitties++)
	{
		double nextNum = 0.0;
		//read next number, if it's less than current lowest, then replace, else do nothing
		nextNum = readNextNumber(infile);
		if (nextNum <= lowest)
		{
			lowest = nextNum;
		}
	}

	printf("Evaluated %d numbers in file.\n", kitties);
	printf("Lowest number is %lf\n\n", lowest);
}
















//all that typical shit I do to end a program, now with 100% more functions!
void typicalEndingShit(void)
{
	printf("\nEnd of program; press Enter to continue");
	char endCharr = '\0';
	scanf("%c", &endCharr);
}