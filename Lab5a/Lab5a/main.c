/*
* Aerie, CS 121
* Instructor: Reynx
* Lab 5 Part 1
* 15 Jun '18
*/

//cats!
#include "raow.h"

int main()
{
	printf(" Lab 5 Part 1\n\n");
	
	//variable declaration
	FILE * infile = NULL;
	int salary = 0;
	
	//open file for read
	infile = openInputFile();

	//calculates moneyz
	salary = computeMoneyz(infile);
	
	//display salary amt
	printf("Salary is $%d\n\n", salary);
	
	//pass judgment based on salary
	passJudgment(salary);

	//close input file
	fclose(infile);

	//closing time!
	printf("\nEnd of program; press Enter to continue");
	//raow
	char endCharr = '\0';
	scanf("%c", &endCharr);

	return 0;
}