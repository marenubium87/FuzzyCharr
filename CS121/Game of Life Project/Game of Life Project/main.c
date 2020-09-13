/*
* Aerie, CS 121
* Instructor: Reynx <3
* Game of Life Project
* 1 Jul 2020
*/

#include "i_have_no_life.h"

int main() {
	
	printf("  Game of Life Project\n");
	printf("  Copyright Prissy Kitty Productions, 2020\n\n");

	//sets up game board and infile for seed locations
	char GoLArray[NUM_ROWS][NUM_COLS] = { '\0' };
	FILE * infile = NULL;
	infile = fopen("input.dat", "r");

	char userInput = '\0';

	do {
		printMenu();
		scanf("%c", &userInput);
		switch (userInput) {
		case '1':
			printRules();
			break;
		case '2':
			printAbout();
			break;
		case '3':
			printOptions();
			break;
		case '4':
			populateLifeGrid(infile, GoLArray);
			getALifeDude(GoLArray, 0);
			break;
		case '5':
			populateLifeGrid(infile, GoLArray);
			getALifeDude(GoLArray, 1);
			break;
		case '6':
			populateLifeGrid(infile, GoLArray);
			getALifeDude(GoLArray, -1);
			break;
		case '7':
			printf("\n\nOkay, bai.\n\n");
			break;
		default:
			printf("\nffs, pick a valid option, man.\n");
			printf("Press enter to try again.\n\n");
			char tempCharr = '\0';
			scanf("%c", &tempCharr);
			scanf("%c", &tempCharr);
			break;
		}
	} while (userInput != '7');

	//close infile, clean up shit
	fclose(infile);
	EoPCleanup();
	return 0;
}


