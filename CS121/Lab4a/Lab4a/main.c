/*
* Aerie, CS 121
* Instructor: Reynx
* Lab 4 Part 1
* 7 Jun '18
*/

//the good stuff.
#include "myshit.h"

int main()
{
	printf(" Lab 4 Part 1\n\n");

	//variable declaration
	FILE * infile = NULL;
	double height = 0.0, weight = 0.0, activityModifier = 0.0, calories = 0.0;
	int isGrill = 0, age = 0;

	//opens text file for reading
	infile = fopen("testdata.dat", "r");

	//must run these four in this exact order
	//text file must have age, gender, height, weight in this exact order, separated by newlines
	/*preconditions:	age:  integer
	*					gender:  m, M, f, or F (characters)
	*					height:  double
	*					weight:  double
	*/				
	age = canIHazAge(infile);
	isGrill = RUAGrill(infile);
	weight = canIHazWeight(infile);
	height = canIHazHeight(infile);
	printf("Finished reading data file.\n");

	//fetches activity modifier from user and returns correct coefficient
	activityModifier = getActivityMultiplier();

	//calculate calories
	calories = calcCalories(age, isGrill, weight, height, activityModifier);

	//output result
	printf("\n");
	printf("The daily caloric need for an individual with parameters as defined\n");
	printf("in the text file, and given the activity level entered above, is: %.0f\n\n", calories);

	//closes file
	fclose(infile);

	printf("End of program; press Enter to continue");
	//kitty prevents program from insta-terminating
	char tempCharr = '\0';
	scanf("%c", &tempCharr);
	scanf("%c", &tempCharr);
	return 0;
}