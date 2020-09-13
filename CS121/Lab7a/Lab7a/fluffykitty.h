//Header file for Lab 7

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
//needed for floor and ceiling functions
#include <math.h>

//opens input file for reading
FILE * openInput(void);

//opens output file for writing
FILE * openOutput(void);

//takes a real number and rounds it to two decimal places
//this function will generate cast/loss of data warnings in the compiler, it's fine
double roundMoney(double rawValue);

//extract the number of hours from the input file
//(it's the fourth number, yo)
double extractHours(FILE * infile);

//given hours, computes total cost and average cost and 
//writes those values to vars pointed to by ptotCost and pavgCost
void computeCost(double hours, double * ptotCost, double * pavgCost);

//writes statements for cost to outfile
//makes a note in console of task
void writeCost(FILE * outfile, double totalCost, double hours, double avgCost);

//returns revenue based on year as described by function in problem statement
double revenueByYear(int year);

//returns the first year that revenue exceeds the input amount, in millions
//directly modifies the variable pointed to by pYear, as practice
void predict(double amount, int * pYear);

//given a year, prints all revenues by year from 1984 until and including the given year to outfile
void printRevenues(FILE * outfile, int finalYear);