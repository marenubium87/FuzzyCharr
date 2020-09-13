/*
* Aerie, CS121
* Instructor: Reynx
* 6 Sep 2018
* Lab 9c - Sorting
*/

#include "AAABCDEEEEEEHHIILLLLOPRRSSSTTTTTY.h"

int main()
{
	printf("Lab 9c - Sorting\n\n");
	int myIntArray[9] = { 33, -2, -5, 11, 25, 61, 27, 17, 8 };
	int myIntArray2[9] = { 22, 65, -13, -4, 1, -54, 19, 24, 5 };
	printf("First array\n");
	print_int_array(myIntArray, 9);
	
	//insertion sort
	insertion_sort_driver(myIntArray, 9);

	printf("Second array\n");
	print_int_array(myIntArray2, 9);

	//bubble sort
	bubble_sort_driver(myIntArray2, 9);

	char tempCharr = '\0';
	printf("End of program; press Enter to continue");
	scanf("%c", &tempCharr);
	return 0;
}