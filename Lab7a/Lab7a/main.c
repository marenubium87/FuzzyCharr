/*
* Aerie, CS121
* Instructor: Reynx
* Lab 7
* 29 Jun 2018
*/

#include "fluffykitty.h"

int main()
{
	printf("  Lab 7 Part A\n\n");
	//variable declaration
	double totalCost = 0.0, avgCost = 0.0, hours = 0.0;
	double * ptotalCost = NULL;
	double * pavgCost = NULL;
	FILE * infile = NULL;
	FILE * outfile = NULL;

	//sets infile and outfile
	infile = openInput();
	outfile = openOutput();

	//sets pointers 
	ptotalCost = &totalCost;
	pavgCost = &avgCost;

	//extracts hours from file
	hours = extractHours(infile);

	//computes cost and average cost
	computeCost(hours, ptotalCost, pavgCost);

	//writes cost and average cost to outfile
	writeCost(outfile, totalCost, hours, avgCost);

	//closes files
	fclose(infile);
	fclose(outfile);

	printf("End of Part A\n\n  Lab 7 Part B\n\n");

	//opens outfile for writing
	outfile = fopen("broadway.txt", "w");

	int criticalYear = 0, criticalRevenue = 1000;
	int * pCriticalYear = &criticalYear;

	//predicts and writes out what year revenues will pass the defined critical amount
	predict(criticalRevenue, pCriticalYear);
	printf("Revenues will exceed %d million dollars in the year %d\n", criticalRevenue, criticalYear);

	//prints all revenues until defined critical year to outfile
	printRevenues(outfile, criticalYear);

	//close outfile
	fclose(outfile);

	//end of program
	printf("End of program, press Enter to continue");
	char tempCharr = '\0';
	scanf("%c", &tempCharr);
	scanf("%c", &tempCharr);
	return 0;
}