//Source file for Corona project
#include "stuffs.h"

//grabs a double from the text file
double grabValue(FILE * infile)
{
	double value = 0.0;
	fscanf(infile, "%lf", &value);
	return value;
}

//wrapper to gather all relevant info from text file
//dependencies:  grabValue(FILE * infile)
void readShit(Stats * myStats, FILE * infile)
{
	//text file must have population, infected, beta, gamma
	//in that exact order, separated by newlines
	//pop and infected in units of people
	//beta and gamma in units of T^(-1)
	//all values will be read as double
	myStats->population = grabValue(infile);
	myStats->inf = grabValue(infile);
	myStats->beta = grabValue(infile);
	myStats->gamma = grabValue(infile);
	printf("DONE.\n\n");
	printf("Parameters are as follows:\n\n");
	printf("Population:   %.0f\n", myStats->population);
	printf("Infected:     %.0f\n", myStats->inf);
	printf("Beta:         %lf\n", myStats->beta);
	printf("Gamma:        %lf\n\n", myStats->gamma);
}

//differential equation for ds/dt
double dsdt(double population, double beta, double sus, double inf)
{
	double dsdt = -beta * sus * inf / population;
	return dsdt;
}

//differential equation for di/dt
//dependencies:  dsdt(population, beta, sus, inf)
double didt(double population, double beta, double gamma, double sus, double inf)
{
	double didt = -dsdt(population, beta, sus, inf) - gamma * inf;
	return didt;
}

//computes one iteration of susceptible using numerical ODE methods)
//dependencies:  dsdt(population, beta, sus, inf)
double computeOneIterationSus(Stats * myStats)
{
	double susNew = 0.0;
	double k1 = 0.0, k2 = 0.0, k3 = 0.0, k4 = 0.0;

	/*
	*i'm just gonna say maybe don't worry about this
	*frankly i'm just parroting the runge-kutta technique as i looked it up
	*okay, fine... as I understand it... k1 - k4 are linear estimates for the new value
	*of y given different estimates for dy/dx at different values of y assuming dx = 1
	*e.g. y = mx+b, thus deltaY = m*deltaX, and m = dy/dx
	*so then, come up with four estimates for dy/dx, k1 - k4...
	*/
	k1 = dsdt(myStats->population, myStats->beta, myStats->sus, myStats->inf);
	k2 = dsdt(myStats->population, myStats->beta, myStats->sus + k1 / 2, myStats->inf);
	k3 = dsdt(myStats->population, myStats->beta, myStats->sus + k2 / 2, myStats->inf);
	k4 = dsdt(myStats->population, myStats->beta, myStats->sus + k3, myStats->inf);

	//...then take this weighted average, valuing k2 and k3 at double the weight
	//of k1 and k4... I don't remember why this works anymore... I knew a decade ago.
	susNew = myStats->sus + (k1 + 2*k2 + 2*k3 + k4)/6.0;
	return susNew;
}

//computes one iteration of infected using numerical ODE methods)
//dependencies:  didt(population, beta, gamma, sus, inf)
double computeOneIterationInf(Stats * myStats)
{
	double infNew = 0.0;
	double k1 = 0.0, k2 = 0.0, k3 = 0.0, k4 = 0.0;
	/*
	*i'm just gonna say maybe don't worry about this
	*frankly i'm just parroting the runge-kutta technique as i looked it up
	*okay, fine... as I understand it... k1 - k4 are linear estimates for the new value
	*of y given different estimates for dy/dx at different values of y assuming dx = 1
	*e.g. y = mx+b, thus deltaY = m*deltaX, and m = dy/dx
	*so then, come up with four estimates for dy/dx, k1 - k4...
	*/
	k1 = didt(myStats->population, myStats->beta, myStats->gamma, myStats->sus, myStats->inf);
	k2 = didt(myStats->population, myStats->beta, myStats->gamma, myStats->sus, myStats->inf + k1 / 2);
	k3 = didt(myStats->population, myStats->beta, myStats->gamma, myStats->sus, myStats->inf + k2 / 2);
	k4 = didt(myStats->population, myStats->beta, myStats->gamma, myStats->sus, myStats->inf + k3);

	//...then take this weighted average, valuing k2 and k3 at double the weight
	//of k1 and k4... I don't remember why this works anymore... I knew a decade ago.
	infNew = myStats->inf + (k1 + 2 * k2 + 2*k3 + k4) / 6.0;
	return infNew;
}

//uses Fourth Order Runge-Kutta numerical ODE technique to
//compute and displays results for all the shit
//dependencies (functions):  computeOneIterationSus, computeOneIterationInf
void goFORKyourself(Stats * myStats)
{
	//initializes containers for sus, inf, and rec
	double tempSus = 0.0, tempInf = 0.0, tempRec = 0.0;
	//header line
	printf("Day     \tSus     \tInf     \tRec\n");
	for (int i = 0; i < myStats->iters; i++)
	{
		//compute values
		tempSus = computeOneIterationSus(myStats);
		tempInf = computeOneIterationInf(myStats);
		tempRec = myStats->population - tempSus - tempInf;

		//prints out values
		printf("%8d\t%8.0f\t%8.0f\t%8.0f\n", i+1, tempSus, tempInf, tempRec);

		//updates values into fields of myStats struct
		myStats->sus = tempSus;
		myStats->inf = tempInf;
		myStats->rec = tempRec;
	}
}