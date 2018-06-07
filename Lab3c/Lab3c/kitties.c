//MROW

//equations for lab 3c

//add header file
#include "kitties.h"

void promptExam(void)
{
	printf("\nEnter your next exam score: ");
}

void promptLab(void)
{
	printf("\nEnter your next lab score: ");
}

void promptProj(void)
{
	printf("\nEnter your next project score: ");
}

//retrieves score for assignment from user as double
double getScore(void)
{
	double score = 0.0;
	scanf("%lf", &score);
	return score;
}

//simple average of two scores in each subsection
double partialAvg(double score1, double score2)
{
	double avg = 0.0;
	avg = (score1 + score2) / (double)2;
	return avg;
}

//precondition:  enter the cumulative average for each subsection
//postcondition:  returns weighted grade for class
double weightAvg(double examAvg, double labAvg, double projAvg)
{
	double avg = 0.0;
	avg = examAvg * EXAMPROP + labAvg * LABPROP + projAvg * PROJPROP;
	return avg;
}