/*
* Aerie, CS121
* Instructor: Reynx
* Lab 3 Part 1
* 6 Jun '18
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> // required for i/o operations
#include <math.h>  // for the power function
#define feetToInches 12 // i think.

double get_weight(void);  //prompts the user for weight in pounds

double get_height(void);  //prompts the user for height in ft

double convert_feet_to_inches(double height_in_feet);  //converts the feet portion of the user's height into inches

double calculate_bmi(double weight_in_pounds, double height_in_inches);  //evaluates BMI based on weight and height

void display_bmi(double bmi);  //displays resultant BMI value to tenths place

int main()
{
	//kitty prevents program from insta-terminating at end
	char tempCharr = '\0';

	printf(" Lab 3 Part 1\n\n");

	//variable declaration
	double weight = 0.0, bmi = 0.0, height = 0.0;

	//prompts user for weight
	weight = get_weight();
	//prompts user for height and get height in inches
	height = convert_feet_to_inches(get_height());
	
	//calculate the BMI
	bmi = calculate_bmi(weight, height);
	//display the BMI
	display_bmi(bmi);


	printf("End of program; press Enter to continue\n");
	scanf("%c", &tempCharr);
	scanf("%c", &tempCharr);

	return 0;
}

//precondition:  none
//postcondition:  user's weight will be returned as double, also newlines twice
double get_weight(void)
{
	double weight = 0.0;
	printf("Enter your weight:  ");
	scanf("%lf", &weight);
	return weight;
	printf("\n\n");
}

//precondition:  none
//postcondition:  user's height in feet will be returned as double, also newlines twice
double get_height(void)
{
	double height = 0.0;
	printf("Enter your height in feet (decimals are okay):  ");
	scanf("%lf", &height);
	return height;
	printf("\n\n");
}

//precondition:  height in feet is a double
//postcondition:  converts feet to inches using conversion factor defined in program
//returns height in inches as double
double convert_feet_to_inches(double height_in_feet)
{
	double height_in_inches = 0.0;
	height_in_inches = height_in_feet * feetToInches;
	return height_in_inches;
}

//precondition:  weight is a double in pounds, height is a double in inches
//postcondition:  calculates the BMI and returns as a double
double calculate_bmi(double weight_in_pounds, double height_in_inches)
{
	double bmi = 0.0;
	bmi = weight_in_pounds * 703 / pow(height_in_inches, 2);
	return bmi;
}

//precondition:  the BMI value must be known, as a double
//postcondition:  the BMI value will be displayed, to the tenths place
//also newlines twice
void display_bmi(double bmi)
{
	printf("\n");
	printf("The BMI is: %.1f", bmi);
	printf("\n\n");
}