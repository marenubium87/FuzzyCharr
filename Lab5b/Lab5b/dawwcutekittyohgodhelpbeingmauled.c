//Source file for Lab 5 Part 2

//yeah, sorry i was bored
#include "dawwcutekittyohgodhelpbeingmauled.h"

//opens data.txt for reading
FILE * openInputFile(void)
{
	FILE * infile = NULL;
	infile = fopen("data.txt", "r");
	return infile;
}

//opens output.txt for writing
FILE * openOutputFile(void)
{
	FILE * outfile = NULL;
	outfile = fopen("output.txt", "w");
	return outfile;
}

//reads next (double) value from infile and returns it
double readMahValue(FILE * infile)
{
	double value = 0.0;
	fscanf(infile, "%lf", &value);
	return value;
}

//takes the average of all elements of infile
//infile must be open for reading
//dependencies:  readMahValue
double takeMahAverage(FILE * infile)
{
	double sum = 0.0, average = 0.0;
	int count = 0;

	//while not end of file, do shit
	while (!feof(infile))
	{
		//reads next value and appends it to sum
		sum += readMahValue(infile);
		//keeps track of number of numbers
		count++;
	}
	//take actual average
	average = sum / (double)count;
	return average;
}

//writes average to outfile
void writeMahAverage(FILE * outfile, double average)
{
	fprintf(outfile, "The average is %.3f", average);
}