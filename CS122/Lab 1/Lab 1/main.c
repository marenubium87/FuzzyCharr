/*
* Aerie, CS122 (!)
* Instructor: Reynx <3
* L1
* 17 Oct 2020
*/

#include "moo.h"

int main(void) {
	printf("CS122, Lab1\n\n");

	//******task 2a starts here
	printf("  **Task 2a (Oops)\n\n");
	char str1[80] = "The quick brown fox bit the l@zy dog's d!ck.";
	char str2[3] = "a";
	char str3[3] = "";
	
	printf("String 1 composition:  ");
	printString(str1);
	printf("\nReversing String 1:  ");
	printString(recurRevString(str1, 0, strlen(str1) - 1));
	printf("\n");
	printf("Checking edge cases...\n\n");
	
	printf("String 2 composition:  ");
	printString(str2);
	printf("\nReversing String 2:  ");
	recurRevString(str2, 0, strlen(str2) - 1);
	printString(str2);
	printf("\n");

	printf("String 3 composition:  ");
	printString(str3);
	printf("\nReversing String 3:  ");
	recurRevString(str3, 0, strlen(str3) - 1);
	printString(str3);
	printf("\n");
	
	system("pause");
	system("cls");
	//******task 2a ends here

	//******task 2b starts here
	printf("  **Task 2b\n\n");
	char inputString[60] = "Donald the dick duck delivered dill due Duesday";
	char delim[10] = "Dd";

	printf("Original input string is:\n");
	printf("\"%s\"\n", inputString);

	printf("\nTokenizing string...\n");
	char * token = NULL;
	token = myStrTok(inputString, delim);
	while (token != NULL) {
		printString(token);
		token = myStrTok(NULL, delim);
	}
	system("pause");
	system("cls");
	//******task 2b ends here

	//******task 2c begins here
	printf("  **Task 2a (Oops)\n\n");
	char testString1[60] = "Hilbert";
	char testString2[60] = "Poincare";
	char targetString1[120] = "";
	char * targetString2 = NULL;
	printf("String 1 original string composition:\n\"%s\"\n\n", testString1);
	qsort(testString1, strlen(testString1), sizeof(char),
		takeBothObjectsAndExamineThemThenDecideWhichGoesAheadOfTheOther);
	printf("String 1 sorted string composition:\n\"%s\"\n\n", testString1);

	printf("String 2 original string composition:\n\"%s\"\n\n", testString2);
	qsort(testString2, strlen(testString2), sizeof(char),
		takeBothObjectsAndExamineThemThenDecideWhichGoesAheadOfTheOther);
	printf("String 2 sorted string composition:\n\"%s\"\n\n", testString2);

	
	printf("Merged string composition(algorithm 1):\n\"%s\"\n\n",
		mergeStrings1(testString1, testString2, targetString1));

	targetString2 = mergeStrings2(testString1, testString2);
	printf("Merged string composition(algorithm 2):\n\"%s\"\n\n", 
		targetString2);
	//we try not to leak memory or dangle pointers in this household
	free(targetString2);
	targetString2 = NULL;

	printf("Merged string composition(algorithm 3):\n\"%s\"\n\n",
		mergeStrings3(testString1, testString2));
	//******task 2c ends here


	system("pause");
	return 0;
}