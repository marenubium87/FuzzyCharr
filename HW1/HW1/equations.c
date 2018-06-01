#define _CRT_SECURE_NO_WARNINGS
/*Pi is delicious*/
#define PI 3.14159
/*Used for gravitational force section*/
#define G 6.67e-11

#include "equations.h"
/*Delicious math goodies including the pow(a,b) function and the sqrt(a) function*/
#include <math.h>

double calculate_newtons_2nd_law(double mass, double acceleration)
{
	double force = 0.0;
	force = mass * acceleration;
	return force;
}

double calculate_volume_cylinder(double radius, double height)
{
	double volume = 0.0;
	volume = PI * pow(radius, 2) * height;
	return volume;
}

char perform_character_encoding(char plaintext_character)
{
	/*defines kitties*/
	char encodedCharr = '\0';
	encodedCharr = (plaintext_character - 'a') + 'A';
	return encodedCharr;
}

double calculate_gravity_force(double mass1, double mass2, double distance)
{
	double force = 0.0;
	force = G * mass1 * mass2 / pow(distance, 2);
	return force;
}

double calculate_resistive_divider(double resistance1, double resistance2, double vin)
{
	double vout = 0.0;
	vout = resistance2 / (resistance1 + resistance2) * vin;
	return vout;
}

double calculate_distance_between_2pts(double x1, double x2, double y1, double y2)
{
	double distance = 0.0;
	distance = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
	return distance;
}

double calculate_general_equation(int a, double x, double z)
{
	double y = 0.0;

	// a basically has to be odd to not break the modulo 2 operation...
	y = (double)73 / 12 - x * z + a / (a % 2);
	return y;
}