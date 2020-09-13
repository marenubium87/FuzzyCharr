/*
* Aerie, CS121
* Instructor: Reynx <3
* Matrix Solver Project, Mark I
* 26 June 2020
*/

#include "abigfluffykittyliveshere.h"

int main() {
	printf("Matrix Solver Mark I\n  Copyright 2020, Prissy Kitty Productions\n\n");

	//load infile and outfile
	FILE * infile = NULL;
	FILE * outfile = NULL;
	infile = fopen("input.dat", "r");
	outfile = fopen("output.dat", "w");
	double augMatrix[NUM_OF_ROWS][NUM_OF_ROWS + 1] = { 0 };

	//grabs value from infile to populate the array.
	populateArray(infile, augMatrix);

	//do shit.
	commitRREF(outfile, augMatrix);

	//all done.
	EoPWrapper();
	return 0;
}