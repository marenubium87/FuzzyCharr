//header file for Corona project

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

//structure containing all relevant variables for this program
//specifically population, sus, inf, rec, beta, gamma, iters
typedef struct stats
{
	double population, sus, inf, rec, beta, gamma;
	int iters;
} Stats;

//wrapper to gather all relevant info from text file
//dependencies:  grabValue(FILE * infile)
double grabValue(FILE * infile);

//wrapper to gather all relevant info from text file
void readShit(Stats * myStats, FILE * infile);

//differential equation for ds/dt
double dsdt(double population, double beta, double sus, double inf);

//differential equation for di/dt
//dependencies:  dsdt(population, beta, sus, inf)
double didt(double population, double beta, double gamma, double sus, double inf);

//computes one iteration of susceptible using numerical ODE methods)
//dependencies:  dsdt(population, beta, sus, inf)
double computeOneIterationSus(Stats * myStats);

//computes one iteration of infected using numerical ODE methods)
//dependencies:  didt(population, beta, gamma, sus, inf)
double computeOneIterationInf(Stats * myStats);

//uses Fourth Order Runge-Kutta numerical ODE technique to
//compute and displays results for all the shit
//dependencies (functions):  computeOneIterationSus, computeOneIterationInf
void goFORKyourself(Stats * myStats);