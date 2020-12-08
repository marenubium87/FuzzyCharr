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
	printf("  Playtime:  %dh %02dm\n",
		targetGame.timePlayed.hours, targetGame.timePlayed.minutes);
	printf("  Achieves:  %d\n", targetGame.numAchieves);
	printf("  Rating:    %d\n", targetGame.rating);
	printf("\n*****\n");
}

//displays game list pointed to by pGameHead to the console
void printGameList(GameNode * pGameHead) {
	GameNode * pCurr = pGameHead;
	while (pCurr != NULL) {
		displayGameContents(pCurr->targetGame);
		pCurr = pCurr->pNext;
	}
	printf("End of list.\n\n");
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

//inserts GameNode containing targetGame to front of game list
//remember to call *location* of pGameHead when calling
void insertGameAtFront(GameNode ** pGameList, Game targetGame) {
	GameNode * pMem = makeGame(targetGame);
	pMem->pNext = *pGameList;
	//need to check if list is not empty... if list is empty, 
	//not necessary (and in fact harmful) to set previous head node's pPrev
	if (*pGameList != NULL) {
		(*pGameList)->pPrev = pMem;
	}
	*pGameList = pMem;
}

//loads game library from infile via insert at front to list
//assumes infile already opened for read
void loadGameLibrary(GameNode ** pGameList, FILE * infile) {
	Game tempGame = { "", "", NULL, { 0, 0 }, 0, 0 };
	char nextLine[1701] = "";
	while (fgets(nextLine, 1700, infile) != NULL) {
		
		//read next game from file

		//set title and dev
		strcpy(tempGame.title, strtok(nextLine, ","));
		strcpy(tempGame.developer, strtok(NULL, ","));
		
		//tokenize genres list
		char * genresList = strtok(NULL, ",");
		//convert playtime, achieves, rating
		tempGame.timePlayed.hours = atoi(strtok(NULL, ":"));
		tempGame.timePlayed.minutes = atoi(strtok(NULL, ","));
		tempGame.numAchieves = atoi(strtok(NULL, ","));
		tempGame.rating = atoi(strtok(NULL, ","));

		//set up genres list
		GenreNode * pTempGenreList = NULL;
		char * tempGenre = NULL;
		tempGenre = strtok(genresList, "|");
		while (tempGenre != NULL) {
			insertGenreAtFront(&pTempGenreList, tempGenre);
			tempGenre = strtok(NULL, "|");
		}
		tempGame.pGenres = pTempGenreList;

		//insert next game into front of list
		insertGameAtFront(pGameList, tempGame);
	}
}
