/*
* Aerie, CS121
* Instructor: Reynx <3
* Strings Lab (9) Re-do
* 12 Jul 2020
*/
#include "lab9.h"

int main() {
	////string declarations to test
	//char str1[80] = "";
	//char str2[80] = "kit";
	//char str3[80] = "cat";
	//char str4[80] = "Kat";

	////length check
	//system("cls");
	//printf("Str1 contents are:  '%s'\n", str1);
	//printf("Str2 contents are:  '%s'\n", str2);
	//printf("Str3 contents are:  '%s'\n", str3);
	//printf("Str4 contents are:  '%s'\n", str4);
	//printf("\n\nString lengths: %d %d %d %d\n\n",
	//	my_strlen(str1), my_strlen(str2), my_strlen(str3), my_strlen(str4));

	//printf("Press enter to continue\n");
	//char tempCharr = '\0';
	//scanf("%c", &tempCharr);

	////string comparison
	//system("cls");
	//printf("Str1 contents are:  '%s'\n", str1);
	//printf("Str2 contents are:  '%s'\n", str2);
	//printf("Str3 contents are:  '%s'\n", str3);
	//printf("Str4 contents are:  '%s'\n", str4);
	//printf("\n");
	//printf("Compare str1 to str2:  %d\n", my_strcmp(str1, str2));
	//printf("Compare str1 to str3:  %d\n", my_strcmp(str1, str3));
	//printf("Compare str1 to str4:  %d\n", my_strcmp(str1, str4));
	//printf("Compare str2 to str3:  %d\n", my_strcmp(str2, str3));
	//printf("Compare str2 to str4:  %d\n", my_strcmp(str2, str4));
	//printf("Compare str4 to str1:  %d\n", my_strcmp(str4, str1));
	//printf("Compare str3 to str1:  %d\n", my_strcmp(str3, str1));
	//printf("Compare str2 to str1:  %d\n", my_strcmp(str2, str1));
	//printf("Compare str1 to str1:  %d\n", my_strcmp(str1, str1));
	//printf("Compare str2 to str2:  %d\n", my_strcmp(str2, str2));

	//printf("\nPress enter to continue\n");
	//scanf("%c", &tempCharr);

	////string cat
	//system("cls");
	//printf("Str1 contents are:  '%s'\n", str1);
	//printf("Str2 contents are:  '%s'\n", str2);
	//printf("Str3 contents are:  '%s'\n", str3);
	//printf("Str4 contents are:  '%s'\n", str4);
	//printf("\n");
	//printf("Appending str3 to str1; str1 is now: '%s'\n", my_strcat(str1, str3));
	//printf("Appending str1 to str4; str4 is now: '%s'\n", my_strcat(str4, str1));
	//printf("Appending str4 to str2; str2 is now: '%s'\n", my_strcat(str2, str4));

	//printf("\nPress enter to continue\n");
	//scanf("%c", &tempCharr);

	//system("cls");
	//printf("Str1 contents are:  '%s'\n", str1);
	//printf("Str2 contents are:  '%s'\n", str2);
	//printf("Str3 contents are:  '%s'\n", str3);
	//printf("Str4 contents are:  '%s'\n", str4);
	//printf("\n");

	//printf("Appending str2 to str4; str4 is now: \n'%s'\n\n", 
	//	my_strcat(str4, str2));
	//printf("Appending str4 to str1; str1 is now: \n'%s'\n\n", 
	//	my_strcat(str1, str4));
	//printf("Appending str1 to str3; str3 is now: \n'%s'\n\n", 
	//	my_strcat(str3, str1));

	//printf("\nPress enter to continue\n");
	//scanf("%c", &tempCharr);

	////strcpy
	//system("cls");
	//printf("Str1 contents are:  '%s'\n", str1);
	//printf("Str2 contents are:  '%s'\n", str2);
	//printf("Str3 contents are:  '%s'\n", str3);
	//printf("Str4 contents are:  '%s'\n", str4);
	//printf("\n");
	//printf("Copying str2 to str4; str4 is now:\n '%s'\n\n", my_strcpy(str4, str2));
	//printf("Copying str3 to str1; str1 is now:\n '%s'\n\n", my_strcpy(str1, str3));
	//printf("Copying str4 to str3; str3 is now:\n '%s'\n\n", my_strcpy(str3, str4));
	//printf("Copying str3 to str1; str1 is now:\n '%s'\n\n", my_strcpy(str1, str3));

	//printf("\nPress enter to continue\n");
	//scanf("%c", &tempCharr);

	char myStrArray[10][50];

	my_strcpy(myStrArray[0], "5abba");
	my_strcpy(myStrArray[1], "Abacus");
	my_strcpy(myStrArray[2], "");
	my_strcpy(myStrArray[3], "alembic");
	my_strcpy(myStrArray[4], "cauldron");
	my_strcpy(myStrArray[5], "porcupine");
	my_strcpy(myStrArray[6], "Paris");
	my_strcpy(myStrArray[7], " parsnip");
	my_strcpy(myStrArray[8], "$500.37");
	my_strcpy(myStrArray[9], "@gmail.com");

	for (int i = 0; i < 10; i++) {
		printf("\"%s\"\n", myStrArray[i]);
	}
	system("pause");

	int compareVal = -2;
	char container[50] = "";
	//moves the marker demarking the sorted portion of the array
	//forward one index each time
	for (int sortedMarker = 9; sortedMarker > 0; sortedMarker--) {

		//increment through the unsorted portion of the array
		for (int i = 0; i < sortedMarker; i++) {

			//compare ith element with i+1th element
			compareVal = my_strcmp(myStrArray[i], myStrArray[i + 1]);
			
			//if i+1th element is less than ith element, swap the two
			if (compareVal == 1) {
				my_strcpy(container, myStrArray[i]);
				my_strcpy(myStrArray[i], myStrArray[i + 1]);
				my_strcpy(myStrArray[i + 1], container);
			}
		}
	}

	for (int i = 0; i < 10; i++) {
		printf("\"%s\"\n", myStrArray[i]);
	}
	system("pause");

	printf("End of output.\n\n");
	system("pause");
	return 0;
}