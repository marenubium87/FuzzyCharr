//CS122 PA2
//29 Nov 2020

#include "sastrugaTest.h"

int testFlag = 0;

int main() {

	srand((unsigned int)time(NULL));

	if (testFlag) {
		//run all tests
		testWrapper();
		system("pause");
	}
	else {
		
		GameNode * pGameHead = NULL;
		GameNode * pCurr = NULL;
		FILE * infile = NULL;
		FILE * outfile = NULL;

		int choice = 0;
		int gameChoice = 0;
		int newRating = 0;

		char tempCharr = '\0';


		do {
			printMenu();
			scanf("%d", &choice);
			system("cls");

			switch (choice) {
			case 1:
				infile = fopen("hereMightBeDragons.csv", "r");
				loadGameLibrary(&pGameHead, infile);
				fclose(infile);
				printf("The new ancient scriptures have been read, my lord.");
				printf("\n\n");
				break;
			case 2:
				outfile = fopen("hereMightBeDragons.csv", "w");
				preserveSacredTeachings(pGameHead, outfile);
				fclose(outfile);
				printf("The sacred teachings have been preserved, master.");
				printf("\n\n");
				break;
			case 3:
				unveilForgottenRecordsWrapper(pGameHead);
				break;
			case 4:
				collectNewArtifact(&pGameHead);
				break;
			case 5:
				banishExile(&pGameHead);
				break;
			case 6:
				rewriteStoneTablets(pGameHead);
				break;
			case 7:
				organizingTroops(&pGameHead);
				break;
			case 8:
				//lets user find game by publisher and start from there
				gameChoice = 0;
				GameNode * gameResultsArray[12] = { NULL };
				while (gameResultsArray[0] == NULL) {

					//populates gameResultsArray with games based on developer
					searchDeveloper(pGameHead, gameResultsArray);

					if (gameResultsArray[0] != NULL) {
						printf("\nType in the entry number of the game\n");
						printf("you wish to judge, or 0 to exit:  ");

						int gameChoice = 0;
						char tempCharr = '\0';
						scanf("%d%c", &gameChoice, &tempCharr);
						if (gameChoice == 0) {
							break;
						}
						else {
							pCurr = gameResultsArray[gameChoice - 1];
						}
						system("cls");
						printf("You have selected:\n\n");
						displayGameContents(pCurr->targetGame);
						printf("Enter a new rating for the game:  ");
						scanf("%d%c", &newRating, &tempCharr);
						decreeDivineJudgment(&(pCurr->targetGame), newRating);
						system("cls");
						displayGameContents(pCurr->targetGame);
						printf("\nGame's rating has been updated.\n");
					}
				}
				break;
			case 9:
				embarkOnQuest(pGameHead);
				break;
			case 10:
				openGatesOfChaos(pGameHead);
				break;
			case 11:
				outfile = fopen("hereMightBeDragons.csv", "w");
				preserveSacredTeachings(pGameHead, outfile);
				fclose(outfile);
				printf("Exiting and preserving the sacred teachings ");
				printf("before departing...\n\n");
				printf("Okay, bai...\n\n");
				break;
			default:
				printf("Please choose a valid option.\n\n");
			}

			system("pause");
			system("cls");
		} while (choice != 11);
		
	}
	return 0;
}