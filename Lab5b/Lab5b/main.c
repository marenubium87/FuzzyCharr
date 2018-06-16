/*
* Aerie, CS 121
* Instructor: Reynx
* Lab 5 Part 2
* 15 Jun '18
*/

//i mean... halp?
#include "dawwcutekittyohgodhelpbeingmauled.h"

int main()
{
	printf(" Lab 5 Part 2");

	//declare vars
	FILE * infile = NULL;
	FILE * outfile = NULL;
	double average = 0.0;

	//sets infile for reading and outfile for writing
	infile = openInputFile();
	outfile = openOutputFile();

	//take average
	average = takeMahAverage(infile);

	//write it to outfile
	writeMahAverage(outfile, average);

	//close those files, yo
	fclose(infile);
	fclose(outfile);
	
	//closing time
	printf("End of program; press Enter to continue");
	char endKitty = '\0';
	scanf("%c", &endKitty);

	return 0;
}