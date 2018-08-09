/*
* Aerie, CS121
* Instructor: Reynx <3
* Lab 8a
*6 Aug 2018
*/

//The source and header files stain easily, so...
//(I have no idea how you put up with me, sometimes.  Well, often.)
#include "warningdontjizzonthis.h"

int main()
{
	printf("Lab 8 Part A\n\n");

	//array declaration
	int myArr[ARRAYSIZE] = { 0 };

	//opens input.txt for reading
	printf("Opening input.txt for read... ");
	FILE * infile = fopen("input.txt", "r");
	printf("done.\n\n");

	//populates array with values from infile and then prints array values for checking
	printf("Populating array with values from input.txt... ");
	populateArray(infile, myArr, ARRAYSIZE);
	printf("done.\n\n");
	printArray(myArr, ARRAYSIZE);

	//reverses array and then prints array values for checking
	printf("\n\nReversing array... ");
	reverseArray(myArr, ARRAYSIZE);
	printf("done.\n\n");
	printArray(myArr, ARRAYSIZE);

	//end of program cleanup
	printf("\n\nEnd of program; press Enter to continue");
	char tempCharr = '\0';
	scanf("%c", &tempCharr);
	scanf("%c", &tempCharr);

	return 0;
}