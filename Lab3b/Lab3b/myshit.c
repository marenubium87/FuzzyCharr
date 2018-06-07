//Equations for lab 3b

//add header file
#include "myshit.h"

//prompts user for a value of theta between 0 and 90 degrees, and returns value as double
//also creates two newlines
double getTheta()
{
	double theta = 0.0;
	printf("Enter the angle of launch in degrees (0 < theta < 90): ");
	scanf("%lf", &theta);
	return theta;
	printf("\n\n");
}

//prompts user for a value of distance for the target in feet, and returns val as double
//also creates two newlines
double getDistance()
{
	double distance = 0.0;
	printf("Enter the distance to the target in feet (> 0): ");
	scanf("%lf", &distance);
	return distance;
	printf("\n\n");
}

//prompts user for the velocity of the projectile in ft/s, and returns val as double
//also creates two newlines
double getVelocity()
{
	double velocity = 0.0;
	printf("Enter the launch velocity for the projectile in ft/s (> 0): ");
	scanf("%lf", &velocity);
	return velocity;
	printf("\n\n");
}

//computes time of flight of projectile in s
//requires distance, velocity, and theta
double computeTime(double distance, double velocity, double theta)
{
	double time = 0.0;
	//converts theta from deg to rad for use in cosine function
	time = distance / (velocity * cos(theta * PI / (double)180));
	return time;
}

//computes height of projectile at location of target
//this value may be negative if the velocity of the projectile is insufficient
//requires time to be computed first in order to function
double computeHeight(double velocity, double theta, double time)
{
	double height = 0.0;
	height = velocity * sin(theta * PI / (double)180) - 0.5 * G * pow(time, 2);
	return height;
}

//print statements describing the time of flight and height at target
void displayResults(double time, double height)
{
	printf("\n");
	printf("The time of flight of the projectile with the stated initial conditions\nis %.3f seconds.\n\n", time);
	printf("The projectile will be at a height of %.3f feet when it reaches the target.\n", height);
	printf("(Note a negative height means the projectile could not make it to the target.)\n\n");
}