/*
* Aerie, CS121
* Instructor: Reynx
* Lab 8b
* 7 Aug 2018
*/

#include "kittysnugglepile.h"

int main()
{
	printf("Lab 8b \n\n");

	//array initialization
	int randArray[20] = { 0 };
	int countArray[101] = { 0 };
	int randArraySize = sizeof(randArray) / sizeof(randArray[0]);
	int countArraySize = sizeof(countArray) / sizeof(countArray[0]);
	
	//seed RNG
	srand((unsigned int)time(NULL));

	//seeds the seedArray with numbers between 1 to 100
	printf("Seeding array of size %d with integers from 1 to %d... ", randArraySize, MAXRAND);
	seedArray(randArray, randArraySize, MAXRAND);
	printf("done.\n\n");

	//initializes output file to write my output to so that you can check my work.
	//oh, the things I do for you...
	FILE * outfile = fopen("output.txt", "w");

	//writes randArray composition to outfile
	printf("Printing contents of seeded array to outfile... ");
	printArrayFile(randArray, randArraySize, outfile);
	printf("done.\n\n");

	//counts elements of randArray
	printf("Counting elements of seeded array... ");
	countIntsArray(randArray, randArraySize, countArray, countArraySize);
	printf("done.\n\n");

	//prints out results of countArray to outfile
	printf("Printing counts to outfile... ");
	fprintf(outfile, "\n\n");
	printCountsFile(countArray, countArraySize, outfile);
	printf("done.\n\n");

	//end of program cleanup
	fclose(outfile);
	printf("End of program; press Enter to continue");
	char tempCharr = '\0';
	scanf("%c", &tempCharr);

	return 0;
}