//source file for Lab 7

#include "fluffykitty.h"

//opens input file for reading and returns the FILE * var for input.txt
 FILE * openInput(void)
{
	FILE * infile = NULL;
	infile = fopen("input.txt", "r");
	return infile;
}

 //opens output file for writing and returns the FILE * var for output.txt
 FILE * openOutput(void)
{
	 FILE * outfile = NULL;
	 outfile = fopen("output.txt", "w");
	 return outfile;
}

 //takes a real number and rounds it to two decimal places
 //this function will generate cast/loss of data warnings in the compiler, it's fine
 double roundMoney(double rawValue)
 {
	 int tempValue = 0;
	 //moves the third decimal position to the ones place and casts to int
	 tempValue = rawValue * 1000;
	 //if the third decimal position is 0-4, round down
	 if (tempValue % 10 < 5)
	 {
		 rawValue = floor(tempValue / (double)10);
	 }
	 //otherwise round up
	 else
	 {
		 rawValue = ceil(tempValue / (double)10);
	 }

	 //divide by 100 to get decimal point back in the correct location
	 rawValue = rawValue / 100;
	 return rawValue;
 }

 //extract the number of hours from infile
 //(it's the fourth number, yo)
 double extractHours(FILE * infile)
 {
	 int tempInt = 0;
	 double tempVal = 0.0;
	 //reads the first three ints from infile and essentially discards them
	 fscanf(infile, "%d", &tempInt);
	 fscanf(infile, "%d", &tempInt);
	 fscanf(infile, "%d", &tempInt);

	 //reads fourth int (which is number of hours) to tempInt and returns it
	 fscanf(infile, "%lf", &tempVal);
	 return tempVal;
 }

 //given hours, computes total cost and average cost and 
 //writes those values to vars pointed to by ptotCost and pavgCost
 void computeCost(double hours, double * ptotCost, double * pavgCost)
 {
	 if (hours - 10 <= 0)
	 {
		 *ptotCost = 7.99;
	 }
	 else
	 {
		 //hours above 10 are charged at 1.99 per hour or partial hour
		 *ptotCost = 7.99 + ceil(hours - 10) * 1.99;
	 }
	 //average cost is total cost divided by hours
	 *pavgCost = *ptotCost / hours;
	 
	 printf("Calculating total cost and average cost.\n\n");
 }

 //writes statements for cost to outfile
 //makes a note in console of task
 void writeCost(FILE * outfile, double totalCost, double hours, double avgCost)
 {
	 fprintf(outfile, "Total cost is $%.2f for %.2f hours\n", totalCost, hours);
	 fprintf(outfile, "Average cost is $%.2f per hour\n", avgCost);

	 printf("Wrote total cost and average cost values to outfile.\n\n");
 }

 //returns revenue based on year as described by function in problem statement
 double revenueByYear(int year)
 {
	 double revenue = 0.0;
	 revenue = 203.265 * pow(1.071, (double)year - 1984);
	 return revenue;
 }

 //returns the first year that revenue exceeds the input amount, in millions
 //directly modifies the variable pointed to by pYear, as practice
 void predict(double amount, int * pYear)
 {
	 //start in 1984
	 *pYear = 1984;
	 //if revenue is still less than amount, increment year and check again
	 while (revenueByYear(*pYear) < amount)
	 {
		 *pYear += 1;
	 }
 }

 //given a year, prints all revenues by year from 1984 until and including the given year to outfile
 void printRevenues(FILE * outfile, int finalYear)
 {
	 int curYear = 1984;
	 while (curYear <= finalYear)
	 {
		 fprintf(outfile, "Revenue in %d - $%.2f million\n", curYear, revenueByYear(curYear));
		 curYear += 1;
	 }
	 //-1 necessary to accurately state the last time successfully ran through loop
	 printf("Wrote all revenues from 1984 to %d into output file.\n\n", curYear - 1);
 }