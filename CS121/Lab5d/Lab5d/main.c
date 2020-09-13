/*
* Aerie, CS 121
* Instructor: Reynx
* Lab 5 Part 4
* 16 Jun '18
*/

//welp.
#include "runningoutofjokes.h"

int main()
{
	printf(" Lab 5 Part 4\n\n");

	//i can haz vars
	FILE * infile = NULL;
	double highest = 0.0, lowest = 0.0;
		
	//sets infile to input.txt
	infile = getInputFile();

	//finds and prints highest number
	printHighest(infile);

	//finds and prints lowest number
	printLowest(infile);

	//close infile
	fclose(infile);

	//all the end stuff but i got bored so i wrote a fcn
	typicalEndingShit();
	return 0;
}