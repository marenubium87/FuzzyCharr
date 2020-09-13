/*
* Aerie, CS 121
* Instructor: Reynx
* Lab 3 Part 3
* 6 Jun 2018
*/

//the soft stuff
#include "kitties.h"

int main()
{
	//mrow
	char tempCharr = '\0';

	printf(" Lab 3 Part 3\n\n");

	//variable declaration
	double exam1 = 0.0, exam2 = 0.0, lab1 = 0.0, lab2 = 0.0, proj1 = 0.0, proj2 = 0.0;
	double examAvg = 0.0, labAvg = 0.0, projAvg = 0.0, totalAvg = 0.0;

	//instructions for user
	printf("Enter grades for assignments as prompted.\n");
	printf("All scores should be greater than zero and nominally out of 100 (E.C. is okay).\n");

	//asks for and stores exam info
	promptExam();
	exam1 = getScore();
	promptExam();
	exam2 = getScore();

	//asks for and stores lab info
	promptLab();
	lab1 = getScore();
	promptLab();
	lab2 = getScore();

	//asks for and stores proj info
	promptProj();
	proj1 = getScore();
	promptProj();
	proj2 = getScore();

	//computes averages
	examAvg = partialAvg(exam1, exam2);
	labAvg = partialAvg(lab1, lab2);
	projAvg = partialAvg(proj1, proj2);
	totalAvg = weightAvg(examAvg, labAvg, projAvg);

	//outputs results
	printf("\n");
	printf("Exam average: %.1f\n", examAvg);
	printf("Lab average: %.1f\n", labAvg);
	printf("Project average: %.1f\n\n", projAvg);

	printf("Cumulative weighted average: %.1f\n\n", totalAvg);

	printf("End of program; press Enter to continue");
	scanf("%c", &tempCharr);
	scanf("%c", &tempCharr);

	return 0;
}