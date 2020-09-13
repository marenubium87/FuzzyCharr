/*
* Aerie, CS121
* Instructor: Reynx
* Lab 3 Part B
* 6 Jun '18
*/

//the good stuff.
#include "myshit.h"

int main()
{
	//mrow
	char tempCharr = '\0';

	//variable declaration
	double theta = 0.0, distance = 0.0, velocity = 0.0, time = 0.0, height = 0.0;

	//get angle, distance, and velocity
	theta = getTheta();
	distance = getDistance();
	velocity = getVelocity();

	//computations, time first as it is required for height calculation
	time = computeTime(distance, velocity, theta);
	height = computeHeight(velocity, theta, time);

	//displays results
	displayResults(time, height);

	printf("End of program; press Enter to continue");
	scanf("%c", &tempCharr);
	scanf("%c", &tempCharr);
}