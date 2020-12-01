//source file for CS122 PA2

#include "sastruga.h"

//prints main Sastruga menu
void printMenu(void) {
	printf("Select an option from the following:\n\n");
	printf("  1.  Read the new ancient scriptures\n");
	printf("  2.  Preserve the sacred teachings\n");
	printf("  3.  Unveil the forgotten records\n");
	printf("  4.  Collect a new artifact\n");
	printf("  5.  Banish the exile\n");
	printf("  6.  Rewrite the stone tablets\n");
	printf("  7.  Organize the troops\n");
	printf("  8.  Decree divine judgment\n");
	printf("  9.  Embark on your next quest\n");
	printf(" 10.  Open the gates of chaos\n");
	printf(" 11.  Retire to your chambers\n");
	printf(" \n\n");
}

//displays all attributes of targetGame to the console
void displayGameContents(Game targetGame) {
	printf("~~\n");
	printf("  Title:     %s\n", targetGame.title);
	printf("  Developer: %s\n", targetGame.developer);
	printf("  Genres:    ");
	printGenreList(targetGame.pGenres);
	printf("\n");
	printf("  Playtime:  %dh%02dm\n",
		targetGame.timePlayed.hours, targetGame.timePlayed.minutes);
	printf("  Achieves:  %d\n", targetGame.numAchieves);
	printf("  Rating:    %d\n", targetGame.rating);
	printf("\n*****\n");
}

//allocates space on the heap for a new GameNode and initializes
//with information found in targetGame
//returns address of GameNode on the heap
GameNode * makeGame(Game targetGame) {
	GameNode * pMem = (GameNode *)malloc(sizeof(GameNode));
	pMem->pNext = NULL;
	pMem->pPrev = NULL;
	strcpy(pMem->targetGame.title, targetGame.title);
	strcpy(pMem->targetGame.developer, targetGame.developer);
	//still need to do genre work here
	pMem->targetGame.pGenres = targetGame.pGenres;
	pMem->targetGame.timePlayed = targetGame.timePlayed;
	pMem->targetGame.numAchieves = targetGame.numAchieves;
	pMem->targetGame.rating = targetGame.rating;
	return pMem;
}