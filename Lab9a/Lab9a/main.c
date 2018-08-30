#include "thiscodingshitshard.h"

/*
*Aerie, CS 121
*Instructor: Reynx
*Lab 9a
*29 Aug 2018
*/

int main()
{
	printf("Lab 9 Part A\n\n");

	//string reversal, using array notation
	printf("  String reversal test\n\n");
	char myStr[30] = "Kitty cat goes maow maow!";
	printf("Original string composition:\n");
	printf("%s", myStr);
	printf("\n\nReversing string...\n");
	printf("Reversed string is:\n");
	printf("%s", string_reverse(myStr));

	//string reversal, using pointer arithmetic
	printf("\n\nReversing string again using alternate reverse function...\n");
	printf("Reverse of reverse (original) string is:\n");
	printf("%s", string_reverse_redux(myStr));

	printf("  \n\nEnd of part A; press Enter to continue\n\n\n");
	char tempCharr = '\0';
	scanf("%c", &tempCharr);

	printf("\n\nLab 9 Part B\n\n");
	//copying strings
	printf("  Copying strings test\n\n");
	char sourceString[30] = "This is my original string";
	char destString[30] = "";
	printf("Printing original string:\n>> ");
	printf("%s", sourceString);
	printf("\n\nCopying and printing copied string:\n>> ");
	printf("%s", my_strcpy(destString, sourceString));

	//concatenating strings
	printf("\n\n  Concatenation test\n\n");
	char concatSource[12] = "aow maow";
	char concatDest[40] = "Kitty consumes your soul, m";
	printf("Destination string is:\n>>  ");
	printf("%s", concatDest);
	printf("\n\nSource (to be appended) string is:\n>>  ");
	printf("%s", concatSource);
	printf("\n\nConcatenating...\n");
	printf("Final Destination (decent horror movie) string is:\n>>  ");
	printf("%s", my_strcat(concatDest, concatSource));

	printf("  \n\npress Enter to continue\n\n\n");
	scanf("%c", &tempCharr);

	//string comparisons
	printf("\n\n  Comparison tests\n\n");
	char cmp1[8] = "kit";
	char cmp2[8] = "kitty";
	char cmp3[8] = "Kitty";
	comparisonWrapper(cmp1, cmp2);
	comparisonWrapper(cmp3, cmp1);
	comparisonWrapper(cmp2, cmp3);
	comparisonWrapper(cmp3, cmp3);

	//end of program cleanup
	printf("End of program; press Enter to continue");
	scanf("%c", &tempCharr);

	return 0;
}