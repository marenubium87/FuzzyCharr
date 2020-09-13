/*
* Aerie, CS121
* Instructor: Reynx
* Lab 1
* 26 May '18
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> /*required for i/o operations*/
#define PI 3.14159 /*required for part e of lab*/

int main()
{
	/*Kitty prevents program from insta-terminating at end*/
	char tempCharr = '\0';

	/* part A */
	{
		printf(" Part A \n\n");

		/* declares required input variables*/
		int number1_int = 0, number2_int = 0;
		double number1_float = 0.0, number2_float = 0.0;

		/*declares required variables for each of the operations*/
		int sumInt = 0, multInt = 0;
		double diffFloat = 0.0;
		int quotIntAsInt = 0, quotFloatAsInt = 0;
		double quotIntAsFloat = 0.0, quotFloatAsFloat = 0.0;
		double castQuot = 0.0;
		int modResult = 0;
		int isIntOneOdd = 0, isIntTwoOdd = 0;
	
		/*Asks user for inputs and stores them into appropriate vars*/
		{
			printf("Enter two integers separated by a space: ");
			scanf("%d %d", &number1_int, &number2_int);
			printf("Now enter two doubles, separated by a space: ");
			scanf("%lf %lf", &number1_float, &number2_float);
		}

		/*Addition/subtraction/product ops*/
		{
			/*Adding ints and printing as int*/
			sumInt = number1_int + number2_int;
			printf("\nAdding ints %d and %d, and printing as int: %d \n",
				number1_int, number2_int, sumInt);

			/*Subtracting floats and printing as float*/
			diffFloat = number1_float - number2_float;
			printf("Subtracting floats %lf and %lf, and printing as float: %lf \n",
				number1_float, number2_float, diffFloat);

			/*Multiplying int and float, printing as int*/
			multInt = number1_int * number1_float;
			printf("Multiplying int %d and float %lf, and printing as int(truncation likely): %d \n",
				number1_int, number1_float, multInt);
		}

		/*Quotient ops*/
		{
			/*Dividing int and int, printing as int and float*/
			quotIntAsInt = number1_int / number2_int;
			quotIntAsFloat = number1_int / number2_int;
			printf("Dividing int %d by int %d as int(truncation likely): %d \n",
				number1_int, number2_int, quotIntAsInt);
			printf("Dividing int %d by int %d as float: %lf \n",
				number1_int, number2_int, quotIntAsFloat);
			/* Note casting the result of an int divided by an int as a float does not "fix" truncation */

			/*Dividing int by float, printing as int and float*/
			quotFloatAsInt = number1_int / number2_float;
			quotFloatAsFloat = number1_int / number2_float;
			printf("Dividing int %d by float %lf as int(truncation likely): %d \n",
				number1_int, number2_float, quotFloatAsInt);
			printf("Dividing int %d by float %lf as float: %lf \n \n",
				number1_int, number2_float, quotFloatAsFloat);
			/* Note dividing int by float and casting as float works "correctly".*/
		}

		/*Casting and modulus ops*/
		{
			/*casting int as float and then dividing by int, printing as float*/
			castQuot = (double)number1_int / number2_int;
			printf("Casting int %d as double and dividing by int %d as float: %lf \n",
				number1_int, number2_int, castQuot);

			/*Casting floats as ints and then taking the modulus*/
			/*(Note that modding floats is illegal*/
			modResult = (int)number1_float / (int)number2_float;
			printf("Casting floats %lf and %lf as ints and then taking the modulus: %d \n",
				number1_float, number2_float, modResult);

			/*Modding ints to determine odd or even*/
			isIntOneOdd = number1_int % 2;
			isIntTwoOdd = number2_int % 2;
			printf("Is %d odd?  (1 = yes, 0 = no): %d \n",
				number1_int, isIntOneOdd);
			printf("Is %d odd?  (1 = yes, 0 = no): %d \n\n",
				number2_int, isIntTwoOdd);
		}

	}

	/* part B */
	{
		printf(" Part B \n\n");

		/*variable declaration*/
		int voltage = 0, current = 0, resistance = 0;

		/*Asks user input*/
		{
			printf("Enter current value as an integer: ");
			scanf("%d", &current);
			printf("Enter resistance value as an integer: ");
			scanf("%d", &resistance);
		}
		
		/*Computes and outputs voltage*/
		{
			voltage = current * resistance;
			printf("The voltage for this circuit is: %d \n\n", voltage);
		}
	}

	/* part C */
	{
		printf(" Part C\n\n");

		/*Variable declaration*/
		int power = 0, voltage = 0, resistance = 0;

		/*Asks for user input*/
		{
			printf("Enter the voltage as an integer: ");
			scanf("%d", &voltage);
			printf("Enter the resistance as an integer: ");
			scanf("%d", &resistance);
		}

		/*Computes and outputs result*/
		{
			power = voltage * voltage / resistance;
			printf("The power in the circuit is: %d \n", power);
			printf("Warning: previous result subject to integer division, truncation is likely \n\n");

		}
	}

	/* part D */
	{
		printf(" Part D \n \n");

		/*declare variables*/
		int a = 0, b = 0, c = 0, d = 0, x = 0, y = 0;

		/*Asks for user input*/
		{
			printf("Evaluation of the polynomial y = 3ax^3 + bx^2/4 + 10cx - 5d\n");
			printf("Type integer coefficients a, b, c, d for polynomial, separated by spaces: ");
			scanf("%d %d %d %d", &a, &b, &c, &d);
			printf("Type integer x-value to evaluate function at: ");
			scanf("%d", &x);
			
		}

		/*Evaluates polynomial and outputs result*/
		{
			y = 3 * a * x * x * x + (double)1 / 4 * b * x * x + 10 * c * x - 5 * d;
			printf("The value of the polynomial with the given inputs is %d \n", y);
			printf("Warning: truncation of result highly likely due to data type\n\n");
		}
	}

	/* part E */
	{
		printf(" Part E \n\n");

		/*Variable declaration*/
		double radius = 0.0, circum = 0.0, fakePi = 0.0;

		/*Ask for user input*/
		{
			printf("Enter radius of circle: ");
			scanf("%lf", &radius);
			printf("Enter value for pi: ");
			scanf("%lf", &fakePi);
			printf("Just kidding - I wouldn't trust you with that.\n");
		}

		/*Computes circumference, outputs result*/
		
			circum = (double) 2 * PI * radius;
			printf("The circumference of the circle with radius %lf is %lf.",
				radius, circum);
		

	}

	scanf("%c", &tempCharr);
	scanf("%c", &tempCharr);
	
	return 0;
}