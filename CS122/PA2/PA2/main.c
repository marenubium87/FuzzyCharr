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
		FILE * infile = NULL;
		FILE * outfile = NULL;

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
				decreeJudgmentWrapper(pGameHead);
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