//Source file for Lab 5 Part 3

//I mean, you know you want to.
#include "playmorespacechem.h"

//opens input.txt for reading
FILE * openInput(void)
{
	FILE * input = NULL;
	input = fopen("input.txt", "r");
	return input;
}

//opens output.txt for writing
FILE * openOutput(void)
{
	FILE * output = NULL;
	output = fopen("output.txt", "w");
	return output;
}

//reads the next int from infile
int readNextNumber(FILE * infile)
{
	int value = 0;
	fscanf(infile, "%d", &value);
	return value;
}

//finds the GCD of a and b and returns as int
int greatest_common_divisor(a, b)
{
	int first = 0, second = 0;
	//get absolute values
	first = abs(a);
	second = abs(b);

	//declare modulus
	int mod = 0;

	do
	{
		//modulus(remainder) of first / second
		mod = first % second;

		//now set second to first and mod to second to prepare to do it again
		//if modulus isn't zero
		first = second;
		second = mod;

	} while (mod != 0);
	
	//the last divisor (which is now first after that swap) is the gcd
	return first;
}

//writes GCD to outfile
void writeGCD(FILE * outfile, int gcd)
{
	fprintf(outfile, "The GCD is: %d", gcd);
}