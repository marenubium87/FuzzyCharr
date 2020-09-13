//header file for lab 4a

#define _CRT_SECURE_NO_WARNINGS
//required for i/o operations
#include <stdio.h>
//probably.
#define FEETTOINCH 12

//defines BMR multipliers for calories as stated in problem description
#define SED 1.2
#define LOW 1.375
#define MOD 1.55
#define HIGH 1.725
#define EXTRA 1.9

//functions to grab data from file
double canIHazWeight(FILE * infile);
double canIHazHeight(FILE * infile);
int canIHazAge(FILE * infile);
int RUAGrill(FILE * infile);

//based on user input, returns one of the activity multiplier amounts listed above
double getActivityMultiplier(void);

//calculates caloric needs based on all of the inputs from the text file and user entered activity level
double calcCalories(int age, int isGrill, double weight, double height, double activityLevel);