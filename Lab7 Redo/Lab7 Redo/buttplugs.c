//source for Lab 7 redo

//oh hell yes!
#include "buttplugs.h"

//reads infile to find hours used, returns hours used
//required for: charges
double readHours(FILE * infile)
{
	//munches away the first three numbers which are not hours
	double output = 0.0;
	fscanf(infile, "%lf", &output);
	fscanf(infile, "%lf", &output);
	fscanf(infile, "%lf", &output);
	//the last number is the # of hours and the one we want to keep
	fscanf(infile, "%lf", &output);
	return output;
}

//takes input as double, rounds it to two decimal points
//returns output as double
double roundMoney(double input)
{
	//rounds to two decimal places by multiplying by 100,
	//applying floor or ceil as appropriate
	//then dividing by 100 again
	double output = 0.0;
	//this forces the the third decimal point into the ones place
	//e.g. for 123.456 -> 123456
	int tempVar = input * 1000;

	//so now use that new ones place to decide round up or down
	//idea is to force that ones place (the 6 in the previous comment)
	//back into the tenths place, and then round up or down as necessary
	//using floor or ceiling function
	if ((tempVar % 10) < 5)
	{
		
		output = floor((double)tempVar / 10);
	}
	else
	{
		output = ceil((double)tempVar / 10);
	}
	//puts it back into dollars and cents
	output /= 100;
	return output;
}

//reads infile for hours used, computes total cost, computes average cost
//updates values to parameters tot and avg
//dependencies:  readHours, roundMoney
void charges(FILE * infile, double * totalCharge, double * avgCost)
{
	double hours = readHours(infile);
	//branches based on whether > 10 hours or not
	if (hours > 10) 
	{
		*totalCharge = 7.99 + ceil(hours - 10)*1.99;
	}
	//otherwise is less than 10 hours, so flat rate
	else 
	{
		*totalCharge = 7.99;
	}
	*avgCost = roundMoney(*totalCharge / hours);
}

//computes revenue based on formula and year
//year is the actual calendar year
//r is set to result of revenue computation, and is in millions of dollars
//required for:  predict, printRev
void revenue(int * year, double * r)
{
	*r = 203.265 * pow(1.071, *year - ZEROYEAR);
}

//year is set to the first year in which the revenue is
//greater than or equal to inputRev
//dependencies:  revenue
void predict(double inputRev, int * year)
{
	int i = ZEROYEAR;
	//a variable that will hold computations for the average revenue
	double actualRev = 0.0;

	//computes once for zero year just in case inputRev is not greater than
	//the revenue for the zero year
	do
	{
		revenue(&i, &actualRev);
		i++;
	} while (inputRev > actualRev);
	*year = i;
}

//prints out table of estimated revenues from 1984 through endYear (inclusive)
//prints out results to outfile
//dependencies:  revenue
void printRev(FILE * outfile, int endYear)
{
	//need this to store the year to year revenue
	double actualRev = 0.0;
	printf("Writing values to outfile... ");
	fprintf(outfile, "Year\tRevenue( x10^6 dollars )\n\n");
	int i = ZEROYEAR;
	while (i <= endYear)
	{
		revenue(&i, &actualRev);
		fprintf(outfile, "%d\t%10.2lf\n", i, actualRev);
		i++;
	}
	printf("done.\n\n");
}