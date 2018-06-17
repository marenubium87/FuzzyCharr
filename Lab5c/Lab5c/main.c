/*
* Aerie, CS 121
* Instructor: Reynx
* Lab 5 Part 3
* 15 Jun '18
*/

#include "playmorespacechem.h"

int main()
{
	printf(" Lab 5 Part 3\n\n");

	//declare variables
	FILE * infile = NULL;
	FILE * outfile = NULL;

	int a = 0, b = 0, gcd = 0;

	//sets infile and outfile
	infile = openInput();
	outfile = openOutput();

	//reads a and b from file
	a = readNextNumber(infile);
	b = readNextNumber(infile);
	printf("Numbers read from input.txt.\n");

	//figure out gcd
	gcd = greatest_common_divisor(a, b);

	//write that to outfile
	writeGCD(outfile, gcd);
	printf("GCD written to output.txt.\n");

	//close files kthx
	fclose(infile);
	fclose(outfile);
	
	//close it all down, boys
	printf("\nEnd of program; press Enter to continue");
	char endCharr = '\0';
	scanf("%c", &endCharr);

	return 0;
}