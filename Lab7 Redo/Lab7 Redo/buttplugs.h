//header file for Lab 7 redo

#define _CRT_SECURE_NO_WARNINGS
#define ZEROYEAR 1984

#include <stdio.h>
//want this for ceiling function
#include <math.h>

//reads infile to find hours used, returns hours used
//required for: charges
double readHours(FILE * infile);

//takes input as double, rounds it to two decimal points
//returns output as double
//required for:  charges
double roundMoney(double input);

//reads infile for hours used, computes total cost, computes average cost
//updates values to parameters tot and avg
//dependencies:  readHours, roundMoney
void charges(FILE * infile, double * totalCharge, double * avgCost);

//computes revenue based on formula and year
//year is the actual calendar year
//r is set to result of revenue computation, and is in millions of dollars
//required for:  predict, printRev
void revenue(int * year, double * r);

//year is set to the first year in which the revenue is
//greater than or equal to inputRev
//dependencies:  revenue
void predict(double inputRev, int * year);

//prints out table of estimated revenues from 1984 through endYear (inclusive)
//prints out results to outfile
void printRev(FILE * outfile, int endYear);