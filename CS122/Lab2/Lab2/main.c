/*
* Aerie, CS122 
* Lab 2
* 22 Nov 2020
*/

#include "lab2.h"
#include "testList.h"

int main() {
	Node * pHead = NULL;
	
	int choice = 0;

	do {
		printMenu();
		scanf("%d", &choice);
		system("cls");
		switch (choice) {
			case 1:
				printAbout();
				break;
			case 2:
				insertContactWrapper(&pHead);
				break;
			case 3:
				deleteContactWrapper(&pHead);
				break;
			case 4:
				printList(pHead);
				break;
			case 5:
				printf("Acquiring contacts from input.dat...  ");
				FILE * infile = fopen("input.dat", "r");
				loadContacts(infile, &pHead);
				fclose(infile);
				printf("done.\n\n");
				break;
			case 6:
				testWrapper();
				break;
			case 7:
				printf("Okay, bai...\n\n");
				break;
			default:
				printf("Please choose a valid option, you dingus.\n\n");
		}
		system("pause");
		system("cls");
	} while (choice != 7);

	return 0;
}