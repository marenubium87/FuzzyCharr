//CS122 PA2
//29 Nov 2020

#include "sastruga.h"

int testFlag = 0;

int main() {

	if (testFlag) {
		//run all your tests
	}

	GameNode * pGameHead = NULL;

	int choice = 0;

	char * testGenre1 = "Apocalyptic";
	char * testGenre2 = "Horror";
	char * testGenre3 = "Kitties";
	char * testGenre4 = "Claws";
	GenreNode * pGenreHead = NULL;
	printGenreList(pGenreHead);
	printf("\n\n");
	insertGenreAtFront(&pGenreHead, testGenre1);
	insertGenreAtFront(&pGenreHead, testGenre2);
	insertGenreAtFront(&pGenreHead, testGenre3);
	insertGenreAtFront(&pGenreHead, testGenre4);
	printGenreList(pGenreHead);
	printf("\n\n");

	Game testGame1 = { "Cow Simulator", "IamMoo Productions", NULL,
	{3, 5}, 5, 6 };
	Game testGame2 = { "Kitty's Terror Spree", "Nefarious Kitty Ltd.", 
		pGenreHead, {9, 40}, 13, 6 };

	displayGameContents(testGame2);
	
	
	

	//***menu bit starts here
	//do {
	//	printMenu();
	//	scanf("%d", &choice);
	//	system("cls");

	//	switch (choice) {
	//	case 1:
	//		break;
	//	case 2:
	//		break;
	//	case 3:
	//		break;
	//	case 4:
	//		break;
	//	case 5:
	//		break;
	//	case 6:
	//		break;
	//	case 7:
	//		break;
	//	case 8:
	//		break;
	//	case 9:
	//		break;
	//	case 10:
	//		break;
	//	case 11:
	//		printf("Okay, bai...\n\n");
	//		break;
	//	default:
	//		printf("Please choose a valid option.\n\n");
	//	}

	//	system("pause");
	//	system("cls");
	//} while (choice != 11);
	//***menu bit ends here

	system("pause");
	return 0;
}