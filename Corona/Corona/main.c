/*
*Aerie
*Instructor: Reynx <3 ILY kthxbai
*Corona Project
*Mar 2020
*/

#include "stuffs.h"

int main()
{
	//variable declaration
	FILE * infile = NULL;
	Stats myStats = { 0.0, 0.0, 0.0, 0.0, 0.0, 0 };

	printf("Reading data from file...   ");

	//opens text file for reading
	//text file must have population, infected, beta, gamma
	//in that exact order, separated by newlines
	//pop and infected in units of people
	//beta and gamma in units of T^(-1)
	//all values will be read as double
	infile = fopen("coeffs.dat", "r");
	readShit(&myStats, infile);
	fclose(infile);

	//initialize susceptible to pop minus infected
	//(because recovered is 0 and s + i + r = pop)
	myStats.sus = myStats.population - myStats.inf;

	//ask for number of iterations
	printf("Enter the number of days to simulate:  ");
	scanf("%d", &myStats.iters);
	printf("\n\n");

	//time to FORK
	//FORK = Fourth-Order Runge-Kutta (numerical ODE algorithm)
	//see en.wikipedia.org/wiki/Runge-Kutta_methods
	goFORKyourself(&myStats);

	//end of program cleanup
	printf("End of program; press Enter to continue");
	//kitty prevents program from insta-terminating
	char tempCharr = '\0';
	scanf("%c", &tempCharr);
	scanf("%c", &tempCharr);
	return 0;
}