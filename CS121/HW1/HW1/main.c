/*
* Aerie, CS121
* Instructor: Reynx
* 1 June 2018
* PA2 (Skipped PA1)
*/

#define _CRT_SECURE_NO_WARNINGS

/*required for i/o operations*/
#include <stdio.h>
/*my custom defined function stack*/
#include "equations.h"

int main()
{
	/* Kitty prevents program from insta-terminating at end */
	char tempCharr = '\0';
	
	/* Newton's second law */

		printf(" Newton's Second Law Calculation\n\n");
		/*Variable declaration*/
		double mass = 0.0, acceleration = 0.0, force = 0.0;
		/*Ask for input*/
		printf("Enter the mass and acceleration \nin the following format (no brackets) [m a]: ");
		scanf("%lf%lf", &mass, &acceleration);
		/*Call predefined function*/
		force = calculate_newtons_2nd_law(mass, acceleration);
		/*Output result*/
		printf("The force is %.2f Newtons.\n\n", force);

	/* Volume of Cylinder */

		printf(" Volume of Cylinder Calculation\n\n");
		/*Variable declaration*/
		double radius = 0.0, height = 0.0, volume = 0.0;
		/*Ask for input*/
		printf("Enter the radius and height of the cylinder \nin the following format (no brackets) [r h]: ");
		scanf("%lf%lf", &radius, &height);
		/*Call predefined function*/
		volume = calculate_volume_cylinder(radius, height);
		/*Output result*/
		printf("The volume is %.2f cubic units.\n\n", volume);

	/* Char Encoding */

		printf(" Character Encoding\n\n");
		/*Kitty declaration*/
		char inputCharr = '\0', encodedCharr = '\0';
		/*Asks for user input*/
		printf("Enter a single character: ");
		scanf(" %c", &inputCharr);
		/*Call predefined function*/
		encodedCharr = perform_character_encoding(inputCharr);
		/*Outputs result*/
		printf("Encoded character is: '%c'\n\n", encodedCharr);

	/* Gravity Force calculation */

		printf(" Gravity Force Calculation\n\n");
		/*Variable declaration*/
		double mass1 = 0.0, mass2 = 0.0, gravDist = 0.0, gravForce = 0.0;
		/*Asks for user input*/
		printf("Enter the values of the two masses in kilograms, separated by a space: ");
		scanf("%lf%lf", &mass1, &mass2);
		printf("Enter the distance between the two masses, in meters: ");
		scanf("%lf", &gravDist);
		/*Call predefined function*/
		gravForce = calculate_gravity_force(mass1, mass2, gravDist);
		/*Outputs result*/
		printf("The gravitational force between these two objects is %.2e Newtons.\n\n", gravForce);

	/* Voltage Divider */
		
		printf(" Resistive Divider Calculation\n\n");
		/*Variable declaration*/
		double r1 = 0.0, r2 = 0.0, vin = 0.0, vout;
		/*Asks for inputs*/
		printf("Enter the two values of the two resistors separated by a space: ");
		scanf("%lf%lf", &r1, &r2);
		printf("Enter the input voltage: ");
		scanf("%lf", &vin);
		/*Call predefined function*/
		vout = calculate_resistive_divider(r1, r2, vin);
		/*Outputs result*/
		printf("The output voltage is %.2f volts.\n\n", vout);

	/* Distance Btwn Two Points */
	
		printf(" Distance Between Two Points Calculation\n\n");
	
		/*variable declaration*/
		double x1 = 0.0, y1 = 0.0, x2 = 0.0, y2 = 0.0, dist = 0.0;
	
		/*Asks for user input*/
		printf("Enter the first point in [x y] format (without brackets): ");
		scanf("%lf%lf", &x1, &y1);
		printf("Enter the second point in [x y] format (without brackets): ");
		scanf("%lf%lf", &x2, &y2);

		/*Call predefined function*/
		dist = calculate_distance_between_2pts(x1, x2, y1, y2);

		/*Print output*/
		printf("The distance between the points (%.2f, %.2f) and (%.2f, %.2f)\nis %.2f\n\n",
			x1, y1, x2, y2, dist);

	/* General Equation Problem */
	
		printf(" General Equation\n\n");
		/*Variable declaration*/
		double x = 0.0, z = 0.0, y = 0.0;
		int a = 0;
		/*Asks for user input*/
		printf("Enter values for x and z, separated by a space: ");
		scanf("%lf%lf", &x, &z);
		printf("Enter a positive odd integer for a: ");
		scanf("%d", &a);
		/*Calls predefined function*/
		y = calculate_general_equation(a, x, z);
		/*Prints output*/
		printf("The value of the general equation\ny = (73/12) - x * z + a / (a %% 2)\nfor the above values of x, y, and a is %.2f\n\n", y);

	printf("End of program; press Enter to continue");
	scanf("%c", &tempCharr);
	scanf("%c", &tempCharr);

	return 0;
}