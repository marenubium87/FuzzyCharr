/*
* Aerie, CS121
* Instructor: Reynx
* Lab 9b (extra credit!)
* 1 Sep 2018
*/

#include "insertcomplaintshere.h"

int main()
{
	printf("Lab 9b - Binary Search\n\n\n");
	printf("First array\n");
	//int myArr1[15] = { -22, -19, -15, -7, -3, -2, 0, 4, 8, 11, 13, 22, 25, 33, 47 };
	
	int myArrA[5] = { 1, 3, 5, 7, 9 };
	bin_search_redux(myArrA, 0, 5);
	bin_search_redux(myArrA, 1, 5);
	bin_search_redux(myArrA, 2, 5);
	bin_search_redux(myArrA, 3, 5);
	bin_search_redux(myArrA, 4, 5);
	bin_search_redux(myArrA, 5, 5);
	bin_search_redux(myArrA, 6, 5);
	bin_search_redux(myArrA, 7, 5);
	bin_search_redux(myArrA, 8, 5);
	bin_search_redux(myArrA, 9, 5);
	bin_search_redux(myArrA, 10, 5);

	//print_int_array(myArr1, 15); 
	//bin_search(myArr1, -22, 0, 14);
	//bin_search(myArr1, -16, 0, 14);
	//bin_search(myArr1, -15, 0, 14);
	//bin_search(myArr1, 47, 0, 14);
	//bin_search(myArr1, 0, 0, 14);
	//bin_search(myArr1, 12, 0, 14);
	//bin_search(myArr1, 33, 0, 14);
	//bin_search(myArr1, 11, 0, 14);
	//bin_search(myArr1, 3, 0, 14);
	//bin_search(myArr1, 4, 0, 14);

	printf("\n\nPress Enter to continue\n\n");
	char tempCharr = '\0';
	//scanf("%c", &tempCharr);

	//printf("Second array\n");
	//int myArr2[12] = { 0, 1, 4, 9, 16, 25, 36, 49, 64, 81, 100, 121 };
	//print_int_array(myArr2, 12);
	//bin_search(myArr2, 4, 0, 11);
	//bin_search(myArr2, 8, 0, 11);
	//bin_search(myArr2, 9, 0, 11);
	//bin_search(myArr2, 13, 0, 11);
	//bin_search(myArr2, 25, 0, 11);
	//bin_search(myArr2, 49, 0, 11);
	//bin_search(myArr2, 65, 0, 11);
	//bin_search(myArr2, 0, 0, 11);
	//bin_search(myArr2, 121, 0, 11);

	//printf("\n\nPress Enter to continue\n\n");
	//scanf("%c", &tempCharr);

	//printf("Third array\n");
	//int myArr3[16] = { -22, -19, -15, -7, -3, -2, 0, 4, 8, 11, 13, 22, 25, 33, 47, 58 };
	//print_int_array(myArr3, 16);
	//bin_search(myArr3, -22, 0, 15);
	//bin_search(myArr3, -20, 0, 15);
	//bin_search(myArr3, -15, 0, 15);
	//bin_search(myArr3, -6, 0, 15);
	//bin_search(myArr3, -2, 0, 15);
	//bin_search(myArr3, 0, 0, 15);
	//bin_search(myArr3, 11, 0, 15);
	//bin_search(myArr3, 23, 0, 15);
	//bin_search(myArr3, 58, 0, 15);


	printf("\n\nEnd of program; press Enter to continue");

	scanf("%c", &tempCharr);
	return 0;
}