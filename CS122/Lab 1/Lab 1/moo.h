//Header for Lab 1

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <Windows.h>
#include <string.h>
#include <stdlib.h>

//aux function, prints target string to console
void printString(char * target);

//reverses target string recursively
//when calling, pass in 0 and strlen - 1 for left and right respectively
//returns reversed string
char * recurRevString(char * target, int left, int right);

//implementation of strTok for task 2b
char * myStrTok(char * str, char * delim);

//comparison function required by qsort
int takeBothObjectsAndExamineThemThenDecideWhichGoesAheadOfTheOther(
	const char * a, const char * b);

//precondition - strings sorcerer and wizard must be presorted
//target needs to have size at least strlen(sorcerer) + strlen(wizard) + 1
//returns target string which is the merge of sorcerer and wizard
char * mergeStrings1(char * sorcerer, char * wizard, char * target);

//precondition - strings sorcerer and wizard must be presorted
//returns target string (on the heap) which is the merge of sorcerer and wizard
char * mergeStrings2(char * sorcerer, char * wizard);

//precondition - strings sorcerer and wizard must be presorted
//merges wizard into sorcerer in sorted order
//returns sorcerer, the string that was merged into
char * mergeStrings3(char * sorcerer, char * wizard);