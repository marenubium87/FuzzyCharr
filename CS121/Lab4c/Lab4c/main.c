/*
* Aerie, CS 121
* Instructor: Reynx
* Lab 4 Part 3
* 10 Jun '18
*/

//grab header
#include "katz.h"

int main()
{
	printf(" Lab 4 Part 3" "\n\n");

	//variable declaration
	FILE * infile = NULL;
	int num1 = 0, num2 = 0, num3 = 0, num4 = 0, num5 = 0;
	double average = 0;

	//opens file for reading
	infile = fopen("mrow.dat", "r");

	//assigns the 5 numbers into local variables
	num1 = getNumber(infile);
	num2 = getNumber(infile);
	num3 = getNumber(infile);
	num4 = getNumber(infile);
	num5 = getNumber(infile);

	//these vars will eventually be 1 if the given number is the smallest, 0 else
	int num1S = 0, num2S = 0, num3S = 0, num4S = 0, num5S = 0;
	//these vars will eventually be 1 if the given number is the largest, 0 else
	int num1L = 0, num2L = 0, num3L = 0, num4L = 0, num5L = 0;
	
	//assigns '1' to the smallest number(s)
	num1S = isSmallest(num1, num2, num3, num4, num5);
	num2S = isSmallest(num2, num1, num3, num4, num5);
	num3S = isSmallest(num3, num1, num2, num4, num5);
	num4S = isSmallest(num4, num1, num2, num3, num5);
	num5S = isSmallest(num5, num1, num2, num3, num4);

	//another tedious process assigns '1' to the largest number(s)
	num1L = isLargest(num1, num2, num3, num4, num5);
	num2L = isLargest(num2, num1, num3, num4, num5);
	num3L = isLargest(num3, num1, num2, num4, num5);
	num4L = isLargest(num4, num1, num2, num3, num5);
	num5L = isLargest(num5, num1, num2, num3, num4);

	printf("Smallest number: ");
	//this tedious block of if/else-ifs prints out the smallest number
	//if multiple numbers are the smallest it'll just grab the first one, so there will be no repeats
	if (num1S == 1)
	{
		printf("%d\n", num1);
	}
	else if (num2S == 1)
	{
		printf("%d\n", num2);
	}
	else if (num3S == 1)
	{
		printf("%d\n", num3);
	}
	else if (num4S == 1)
	{
		printf("%d\n", num4);
	}
	else if (num5S == 1)
	{
		printf("%d\n", num5);
	}

	printf("Largest number: ");
	//this tedious block of does the same thing only with largest number
	//if multiple numbers are the largest it'll just grab the first one, so there will be no repeats
	if (num1L == 1)
	{
		printf("%d\n", num1);
	}
	else if (num2L == 1)
	{
		printf("%d\n", num2);
	}
	else if (num3L == 1)
	{
		printf("%d\n", num3);
	}
	else if (num4L == 1)
	{
		printf("%d\n", num4);
	}
	else if (num5L == 1)
	{
		printf("%d\n", num5);
	}

	//and finally the average
	average = takeAverage(num1, num2, num3, num4, num5);
	printf("The average is: %.2f\n\n", average);

	//closes file
	fclose(infile);

	printf("End of program; press Enter to continue");
	//kitty says no to insta-termination
	char tempCharr = '\0';
	scanf("%c", &tempCharr);
	scanf("%c", &tempCharr);

	return 0;
}