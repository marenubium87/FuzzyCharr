/*
* Aerie, CS 121
* Instructor: Reynx
* PA 3
* 14 Jun '18
*/

//grabs header file
#include "stuffstuffstuff.h"

int main()
{
	printf(" PA 3\n\n");

	//variable declaration
	FILE * infile = NULL;
	FILE * asciiOut = NULL;
	FILE * statOut = NULL;
	
	//set input and output files
	infile = open_input_file();
	asciiOut = fopen("output_ascii.dat", "w");
	statOut = fopen("output_stats.dat", "w");
	printf("Opened input and output files.\n");

	//get all the ascii values and output them to output_ascii.dat
	do_ascii_shit_ten(infile, asciiOut);
	printf("Finished writing ascii values to output_ascii.dat... \n");

	//prints shit to stats file
	print_number_lines(infile, statOut);
	print_number_vowels(infile, statOut);
	print_number_digits(infile, statOut);
	print_number_alphas(infile, statOut);
	print_number_lowers(infile, statOut);
	print_number_uppers(infile, statOut);
	print_number_spaces(infile, statOut);
	print_number_alnums(infile, statOut);
	print_number_puncts(infile, statOut);
	printf("Finished writing stats to output_stats.dat...\n");

	//close all files
	fclose(infile);
	fclose(asciiOut);
	fclose(statOut);
	printf("Closed input and output files.\n");

	//Closed for business
	printf("\nEnd of program; press Enter to continue");
	char endingCharr = '\0';
	scanf("%c", &endingCharr);

	return 0;
}