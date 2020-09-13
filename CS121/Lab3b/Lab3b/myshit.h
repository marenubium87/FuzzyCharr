//Header file for Lab 3b

#define _CRT_SECURE_NO_WARNINGS

//grav constant
#define G 32.17
//yum yum pi!
#define PI 3.14159

//required for i/o operations
#include <stdio.h>
//required for happy trig functions
#include <math.h>

//prompts user for and stores an angle, in degrees
double getTheta();

//prompts user for a distance to the target, in feet
double getDistance();

//prompts user for the velocity of the projectile in ft/s
double getVelocity();

//computes time of flight of the projectile, in s
double computeTime(double distance, double velocity, double theta);

//computes height of projectile at location of target, in ft
double computeHeight(double velocity, double theta, double time);

//displays results for time and height as doubles
void displayResults(double time, double height);