//CS122 PA2
//29 Nov 2020

#include "sastrugaTest.h"

int testFlag = 0;

int main() {

	if (testFlag) {
		//run all your tests
		testWrapper();
	}
	else {
		
		GameNode * pGameHead = NULL;
		FILE * infile = NULL;

		int choice = 0;

		do {
			printMenu();
			scanf("%d", &choice);
			system("cls");

			switch (choice) {
			case 1:
				infile = fopen("hereMightBeDragons.csv", "r");
				loadGameLibrary(&pGameHead, infile);
				fclose(infile);
				break;
			case 2:
				break;
			case 3:
				printGameList(pGameHead);
				break;
			case 4:
				break;
			case 5:
				break;
			case 6:
				break;
			case 7:
				break;
			case 8:
				break;
			case 9:
				break;
			case 10:
				break;
			case 11:
				//incomplete!  need to preserve sacred teachings here as well

				printf("Okay, bai...\n\n");
				break;
			default:
				printf("Please choose a valid option.\n\n");
			}

			system("pause");
			system("cls");
		} while (choice != 11);
		
	}

	system("pause");
	return 0;
}