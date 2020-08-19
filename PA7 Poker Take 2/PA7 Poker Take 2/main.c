/*
* Aerie, CS121
* Instructor: Reynx <3
* PA7 Poker
* 5 Aug 2020
*/

#include "pokeypoke.h"


int main(void) {

	char userInput = '\0';
	do {
		system("cls");
		printf("\nLet's play a game!\n");
		printMenu();
		scanf(" %c", &userInput);
		
		switch (userInput) {
		case '1':
			system("cls");
			printf("\nVery funny.  But no.\n\n");
			system("pause");
			break;
		case '2':
			system("cls");
			printf("\nI have a better idea.  King yourself, asshole.\n\n");
			system("pause");
			break;
		case '3':
			system("cls");
			printf("\nNo, and fuck you in particular.\n\n");
			system("pause");
			break;
		case '4':
			playPoker();
			break;
		case '5':
			playThermonuclearWar();
			break;
		case '6':
			printf("\nOkay, bai.\n\n");
			break;
		default:
			printf("\nCom'on, pick a valid option.\n\n");
			system("pause");
			break;
		}
	} while (userInput != '6');

	system("pause");
	return 0;
}

