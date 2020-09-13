/*
* Aerie, CS 121
* Instructor: Reynx <3
* PA6:  Battleship Program
* 5 Jul 2020
*/

#include "battleship.h"

int main() {
	//seed random number generator
	srand((unsigned int)time(NULL));

	//sets up trueSight
	int trueSight = 0;
	//menu options here
	char userInput = '\0';
	do {
		system("cls");
		printf("  Battleship - The Game\n");
		printf("  A Prissy Kitty Production, Copyright 2020\n\n\n");
		printMenu();
		scanf(" %c", &userInput);
		switch (userInput) {
		case '1':
			printAboutBattleship();
			break;
		case '2':
			printAboutCompany();
			break;
		case '3':
			printAboutTrueSight(&trueSight);
			break;
		case '4':
			playBattleship(&trueSight);
			break;
		case '5':
			printf("\n\nOkay, bai.\n\n");
			break;
		default:
			printf("\nCom'on, pick a valid option.\n");
			printf("Press enter to try again.\n\n");
			char tempCharr = '\0';
			scanf("%c", &tempCharr);
			scanf("%c", &tempCharr);
			break;
		}
	} while (userInput != '5');

	EoPCleanup();
	return 0;
}