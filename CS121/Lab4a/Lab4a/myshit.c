//Source file for Lab 4 Part 1

//grabs header file
#include "myshit.h"

//next 4 retrieve data from text file.  
//WARNING!  they must be run in a certain order and text file must have data in a certain order.
//see relevant section in main.c for more information
int canIHazAge(FILE * infile)
{
	int age = 0;
	fscanf(infile, "%d", &age);
	return age;
}

int RUAGrill(FILE * infile)
{
	int isGrill = 0;
	//heh, sex.  okay, moving on.
	char sex = '\0';
	fscanf(infile, " %c", &sex);

	//returns 1 if grill, 0 if dood, and uh... 0 if attack helicopter
	//but the program will at least yell at you to let you know that's not ok
	switch (sex)
	{
	case 'f':
	case 'F': isGrill = 1;
		break;
	case 'm':
	case 'M': isGrill = 0;
		break;
	default: printf("Data error; you cannot identify as an attack helicopter.\n\n");
		break;
	}

	return isGrill;
}

double canIHazWeight(FILE * infile)
{
	double weight = 0.0;
	fscanf(infile, "%lf", &weight);
	return weight;
}

//input height in feet, return height in inches
double canIHazHeight(FILE * infile)
{
	double height = 0.0;
	fscanf(infile, "%lf", &height);

	//converts to inches
	return height * FEETTOINCH;
}

//gets the activity level modifier as defined in header file, based on user input
double getActivityMultiplier(void)
{
	char activity = '\0';
	double activityMultiplier = 0.0;

	printf("\n");
	printf("Enter the activity level for this individual\n");
	printf("(Type THE FIRST LETTER of the activity level from the options below)\n");
	printf("(Not case-sensitive)\n\n");

	printf("-Sedentary\n");
	printf("-Low activity\n");
	printf("-Moderate activity\n");
	printf("-High activity\n");
	printf("-Extra activity\n");

	printf("\n");

	scanf(" %c", &activity);
	
	//picks the correct coefficient based on header file for each activity level
	switch (activity) 
	{
	case 's':
	case 'S': activityMultiplier = SED;
		break;
	case 'l':
	case 'L': activityMultiplier = LOW;
		break;
	case 'm':
	case 'M': activityMultiplier = MOD;
		break;
	case 'h': 
	case 'H': activityMultiplier = HIGH;
		break;
	case 'e':
	case 'E': activityMultiplier = EXTRA;
		break;
	default:  printf("Input error... did you seriously fuck up typing a single letter?\n\n");
		break;
	}

	return activityMultiplier;
}

//calculates caloric needs given all of the inputs - 4 from text file, one from user input
double calcCalories(int age, int isGrill, double weight, double height, double activityLevel)
{
	double BMR = 0.0, calories = 0.0;
	//formulae are different depending on grill or not
	if (isGrill == 1)
	{
		BMR = 655 + (4.35 * weight) + (4.7 * height) - (4.7 * age);
	}
	else if (isGrill == 0)
	{
		BMR = 66 + (6.23 * weight) + (12.7 * height) - (6.8 * age);
	}
	else
	{
		printf("Error code 69: contact your programmer.\n\n");
	}

	//multiply by the activity level modifier
	calories = BMR * activityLevel;
	return calories;
}