/*
* Aerie, CS 121
* Instructor: Reynx
* Lab 2
* 31 May '18
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> /*required for i/o operations*/

int main()
{
	/*Kitty prevents program from abruptly terminating at end*/
	char tempCharr = '\0';

	/* Part 1 */
	
		printf("\n Part 1\n");

		/*Variable declaration*/
		double x1 = 0.0, y1 = 0.0, x2 = 0.0, y2 = 0.0;
		double xMid = 0.0, yMid = 0.0, slope = 0.0, perpSlope = 0.0, yIntercept = 0.0;

		/*Asks user for input of the two points*/
		printf("\nEnter the first point in the format [x1 y1] (without brackets): ");
		scanf("%lf%lf", &x1, &y1);
		printf("Warning!  Second point cannot be horizontally or vertically \naligned with first point.\n");
		printf("\nEnter the second point in the format [x2 y2] (without brackets): ");
		scanf("%lf%lf", &x2, &y2);

		/*Midpoint computation*/
		xMid = (x1 + x2) / 2;
		yMid = (x2 + y2) / 2;

		/*Slope and slope of perpendicular bisector computation, y-int computation*/
		slope = (y2 - y1) / (x2 - x1);
		perpSlope = -1 / slope;
		yIntercept = yMid - perpSlope * xMid;

		/*Prints results*/
		printf("\nThe equation of the perpendicular bisector to the line \ncontaining the points (%.3f, %.3f) and (%.3f, %.3f) is\n\n", 
			x1, y1, x2, y2);
		printf("y = %.3f * x + %.3f\n", perpSlope, yIntercept);

	/* Part 2 */
		
		printf("\n Part 2\n\n");

		/*Variable declaration*/
		int feet = 0;
		double inches = 0.0, height = 0.0, weight = 0.0, fakeWeight = 0.0, bmi = 0.0;

		/*Asks user for inputs*/
		printf("Enter your height in the format [feet inches] (without brackets): ");
		scanf("%d%lf", &feet, &inches);
		printf("Now enter your weight, in pounds: ");
		scanf("%lf", &fakeWeight);
		printf("Really?  You're not fooling anyone.  Put in your weight, and be honest: ");
		scanf("%lf", &weight);

		/*Computation of height and BMI*/
		height = feet * 12 + inches;
		bmi = weight * 703 / (height * height);

		/*Prints output*/
		printf("\nYour BMI is %.2f.\n", bmi);
	
	/* Part 3 */

		printf("\n Part 3\n\n");

		/* Variable declaration*/
		int harris_raw = 0, coaches_raw = 0;
		double harris_poll = 0.0, coaches_poll = 0.0, computer_ranking = 0.0, BCS_score = 0.0;

		/*Prompts user for inputs*/
		printf("Enter the Harris poll score (a positive integer <= 2850): ");
		scanf("%d", &harris_raw);
		printf("Enter the Coaches' poll score (a positive integer <= 1475): ");
		scanf("%d", &coaches_raw);
		printf("Enter the computer ranking (a decimal between 0 and 1): ");
		scanf("%lf", &computer_ranking);

		/*Calculates Harris and Coaches rankings, and total BCS score*/
		harris_poll = harris_raw / (double)2850;
		coaches_poll = coaches_raw / (double)1475;
		BCS_score = (harris_poll + coaches_poll + computer_ranking) / 3;

		/*Prints results*/
		printf("\n");
		printf("Harris ranking:    %.4f\n", harris_poll);
		printf("Coaches' ranking:  %.4f\n", coaches_poll);
		printf("Computer ranking:  %.4f\n", computer_ranking);
		printf("\nBCS total score: %.4f\n", BCS_score);
	
	printf("\nEnd of program, press enter to continue");
	scanf("%c", &tempCharr);
	scanf("%c", &tempCharr);

	return 0;
}