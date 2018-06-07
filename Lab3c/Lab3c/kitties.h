//mrow
//header file for Lab 3c

#define _CRT_SECURE_NO_WARNINGS

//required for i/o operations
#include <stdio.h>

//defines percentage weighting for each assignment type
//sigma(proportions) = 1
#define EXAMPROP 0.6
#define LABPROP 0.1
#define PROJPROP 0.3

//asks user to input score for each type of assignment - does not take input
void promptExam(void);
void promptLab(void);
void promptProj(void);

//retrieves score for assignment from user
double getScore(void);

//gets the average of the two scores for each type of assignment
double partialAvg(double score1, double score2);

//gets the weighted average of all scores according to the weight proportion defined above
double weightAvg(double examAvg, double labAvg, double projAvg);