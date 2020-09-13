/*
*Aerie, CS121
*Instructor: Reynx <3
*Lab 7 Redo
*16 June '20
*/

//mmmm
#include "buttplugs.h"

int main()
{
	printf("    Lab 7 Redo\n\n");
	printf("Doing part A... ");
	//variable setup for 7a
	double totalCharge = 0.0;
	double avgCost = 0.0;
	/*alternative version
	*double * pTotalCharge = &totalCharge;
	*double * pAvgCost = &avgCost;
	*/

	//set up file ops
	FILE * infile = NULL;
	FILE * outfile = NULL;
	infile = fopen("lab7aInput.dat", "r");
	outfile = fopen("lab7aOutput.dat", "w");

	charges(infile, &totalCharge, &avgCost);

	/*alternative version
	*charges(infile, pTotalCharge, pAvgCost);
	*/

	fprintf(outfile, "Your total charge is:  $%.2lf\n", totalCharge);
	fprintf(outfile, "Average cost per hour is:  $%.2lf\n", avgCost);

	//close files for 7a
	fclose(infile);
	fclose(outfile);
	printf("done.  Check your output.\n\n");
	
	//start 7b
	//$1 trillion is a million millions.
	double inputRevenue = 1000000.0;
	printf("Doing part B...\n");

	//reassign outfile
	outfile = fopen("lab7bOutput.dat", "w");

	//need these two variables declared so they can be passed in
	double actualRev = 0.0;
	int endYear = 0;
	
	//assigns endYear to the correct year to exceed one trillion dollars
	predict(inputRevenue, &endYear);
	printf("The first year revenues will exceed %.2lf millions is %d.\n\n", inputRevenue, endYear);
	printRev(outfile, endYear);

	fclose(outfile);
	//end of prog cleanup
	printf("End of program, press enter to continue\n");
	char tempCharr = '\0';
	scanf("%c", &tempCharr);
	return 0;
}