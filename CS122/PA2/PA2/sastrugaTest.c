//source file for sastruga test functions

#include "sastrugaTest.h"

//wrapper to run all tests
void testWrapper(void) {

	//testInsertGameAtFront();
	//testLoadGameLibrary();
	//testModifyGenres();
	//testDecreeDivineJudgment();
	//testRemoveSelectedGame();

	testOrganizingTroops();
	system("pause");
}

//aux function for other tests
//deletes target list by freeing memory and resetting pointer to NULL
void deleteGenreList(GenreNode ** pGenreList) {
	GenreNode * pTemp = NULL;
	while (*pGenreList != NULL) {
		//deletes first element repeatedly
		pTemp = *pGenreList;
		*pGenreList = pTemp->pNext;
		free(pTemp);
	}
}

//aux function for other tests
//delete target game list by freeing memory and resetting pointer to NULL
void deleteGameList(GameNode ** pGameList) {
	GameNode * pTemp = NULL;
	while (*pGameList != NULL) {
		//deletes first element repeatedly
		pTemp = *pGameList;
		*pGameList = pTemp->pNext;
		free(pTemp);
	}
}

//aux function for other tests
//returns 1 if the two genre lists are identical in entries and order, 0 else
int compareGenreLists(GenreNode * genreList1, GenreNode * genreList2) {
	//both lists have entries remaining
	while (genreList1 != NULL && genreList2 != NULL) {
		//do the entries fail to match?
		if (strcmp(genreList1->genre, genreList2->genre) != 0) {
			return 0;
		}
		else {
			genreList1 = genreList1->pNext;
			genreList2 = genreList2->pNext;
		}
	}
	//at least one of the lists has no more entries remaining
	//does one of the lists still have entries remaining?
	if (genreList1 != NULL || genreList2 != NULL) {
		return 0;
	}
	else {
		//both lists were identical and terminated after the same # of entries
		return 1;
	}
}

//aux function for other tests
//returns 1 if game1's fields match game2's fields perfectly, 0 else
//dependencies:  compareGenreLists
int compareGames(Game game1, Game game2) {
	int i = 0;
	if (strcmp(game1.title, game2.title) == 0) {
		i++;
	}
	if (strcmp(game1.developer, game2.developer) == 0) {
		i++;
	}
	if (game1.numAchieves == game2.numAchieves) {
		i++;
	}
	if (game1.rating == game2.rating) {
		i++;
	}
	if (game1.timePlayed.hours == game2.timePlayed.hours) {
		i++;
	}
	if (game1.timePlayed.minutes == game2.timePlayed.minutes) {
		i++;
	}
	i += compareGenreLists(game1.pGenres, game2.pGenres);
	if (i == 7) {
		return 1;
	}
	else {
		return 0;
	}
}

//aux function for other tests
//returns 1 if pGameList1's entries all match pGameList2's entries, 0 else
//NOTE this function will return 0 if both lists have the same games,
//but in a different order!
//dependencies:  compareGames
int compareGameLists(GameNode * gameList1, GameNode * gameList2) {
	GameNode * gameList1Prev = NULL;
	GameNode * gameList2Prev = NULL;

	//are both lists empty?
	if (gameList1 == NULL && gameList2 == NULL) {
		return 1;
	}
	//check first elements
	if (compareGames(gameList1->targetGame, gameList2->targetGame) == 0) {
		return 0;
	}
	else {
		gameList1Prev = gameList1;
		gameList2Prev = gameList2;
		gameList1 = gameList1->pNext;
		gameList2 = gameList2->pNext;
	}

	//both lists have entries remaining
	while (gameList1 != NULL && gameList2 != NULL) {
		if (compareGames(gameList1->targetGame, gameList2->targetGame) == 0) {
			return 0;
		}
		//do the pPrevs point to the correct places?
		else if (gameList1->pPrev != gameList1Prev ||
				gameList2->pPrev != gameList2Prev) {
			return 0;
		}
		else {
			gameList1Prev = gameList1;
			gameList2Prev = gameList2;
			gameList1 = gameList1->pNext;
			gameList2 = gameList2->pNext;
		}
	}
	//does one list terminate but the other one not?
	if (gameList1 != NULL || gameList2 != NULL) {
		return 0;
	}

	//if code makes it to here, both lists are identical
	return 1;
}

//test function for loading game library from file
//returns 1 if test passed, 0 else
//also displays results of test to console
int testLoadGameLibrary(void) {
	printf("\n  ***TEST LOADING GAME LIBRARY...\n");
	FILE * infile = fopen("testInput.csv", "r");

	//setting up reference games and genre nodes
	Game testGame1 = { "Cow Simulator", "TastyMoo Corp", NULL,
	{ 3, 5 }, 5, 6 };
	Game testGame2 = { "Kitty's Terror Spree", "Nefarious Kitty Ltd.", NULL,
	{ 9, 40 }, 13, 5 };
	Game testGame3 = { "Beef Cooking Simulator", "TastyMoo Corp", NULL,
	{ 1, 23 }, 99, 4 };
	Game testGame4 = { "Dark Souls 638", "Form Hardware", NULL,
	{ 587, 45 }, 166, 2 };

	GenreNode * pTestGame1Genres = NULL;
	GenreNode * pTestGame2Genres = NULL;
	GenreNode * pTestGame3Genres = NULL;
	GenreNode * pTestGame4Genres = NULL;

	insertGenreAtFront(&pTestGame4Genres, "Story-Rich");
	insertGenreAtFront(&pTestGame4Genres, "YOU DIED");
	insertGenreAtFront(&pTestGame3Genres, "RTS");
	insertGenreAtFront(&pTestGame3Genres, "Story-Rich");
	insertGenreAtFront(&pTestGame2Genres, "Adventure");
	insertGenreAtFront(&pTestGame2Genres, "Action");
	insertGenreAtFront(&pTestGame2Genres, "Kitties");
	insertGenreAtFront(&pTestGame1Genres, "Violent");
	insertGenreAtFront(&pTestGame1Genres, "RPG");

	testGame1.pGenres = pTestGame1Genres;
	testGame2.pGenres = pTestGame2Genres;
	testGame3.pGenres = pTestGame3Genres;
	testGame4.pGenres = pTestGame4Genres;

	GameNode * pRefGameList = NULL;
	insertGameAtFront(&pRefGameList, testGame1);
	insertGameAtFront(&pRefGameList, testGame2);
	insertGameAtFront(&pRefGameList, testGame3);
	insertGameAtFront(&pRefGameList, testGame4);

	GameNode * pTestGameHead = NULL;
	loadGameLibrary(&pTestGameHead, infile);

	int testPassedFlag = compareGameLists(pTestGameHead, pRefGameList);

	//cleanup; we don't leak memory in this household
	deleteGenreList(&pTestGame1Genres);
	deleteGenreList(&pTestGame2Genres);
	deleteGenreList(&pTestGame3Genres);
	deleteGenreList(&pTestGame4Genres);

	deleteGameList(&pTestGameHead);
	deleteGameList(&pRefGameList);
	
	if (testPassedFlag) {
		printf("PASSED\n\n");
		return 1;
	}
	else {
		printf("FAILED\n\n");
		return 0;
	}
}

//test function for modifying genres inside rewriting tablets fcn
//returns 1 if *all* tests passed, 0 else
//also displays results of tests to console
int testModifyGenres(void) {
	GenreNode * pTestHead = NULL;
	GenreNode * pRefHead = NULL;
	GenreNode * pMem = NULL;
	int numTestsPassed = 0;

	//sets up test list to be identical to reference list at start
	pTestHead = (GenreNode *)malloc(sizeof(GenreNode));
	strcpy(pTestHead->genre, "RTS");
	pTestHead->pNext = NULL;
	
	pMem = (GenreNode *)malloc(sizeof(GenreNode));
	strcpy(pMem->genre, "kitties");
	pTestHead->pNext = pMem;
	pMem->pNext = NULL;

	pRefHead = (GenreNode *)malloc(sizeof(GenreNode));
	strcpy(pRefHead->genre, "RTS");
	pRefHead->pNext = NULL;

	pMem = (GenreNode *)malloc(sizeof(GenreNode));
	strcpy(pMem->genre, "kitties");
	pRefHead->pNext = pMem;
	pMem->pNext = NULL;

	//delete a valid entry
	printf("\n  ***TEST GENRE MODIFICATIONS...\n");
	printf("Testing deleting genre...  \n");
	modifyGenreList(&pTestHead, "kitties");
	pMem = pRefHead->pNext;
	free(pMem);
	pMem = NULL;
	pRefHead->pNext = NULL;
	
	if (compareGenreLists(pTestHead, pRefHead)) {
		numTestsPassed++;
		printf("PASSED\n\n");
	}
	else {
		printf("FAILED\n\n");
	}

	//attempting to delete the last genre from the list
	printf("Testing deleting last genre from list...  \n");
	modifyGenreList(&pTestHead, "RTS");
	if (compareGenreLists(pTestHead, pRefHead)) {
		numTestsPassed++;
		printf("PASSED\n\n");
	}
	else {
		printf("FAILED\n\n");
	}

	//adding an entry
	printf("Testing adding genre...  ");
	modifyGenreList(&pTestHead, "nuclear war");
	pMem = (GenreNode *)malloc(sizeof(GenreNode));
	strcpy(pMem->genre, "nuclear war");
	pMem->pNext = pRefHead;
	pRefHead = pMem;
	if (compareGenreLists(pTestHead, pRefHead)) {
		numTestsPassed++;
		printf("PASSED\n\n");
	}
	else {
		printf("FAILED\n\n");
	}

	//cleanup
	deleteGenreList(&pTestHead);
	deleteGenreList(&pRefHead);

	printf("%d of 3 genre modification tests passed\n", numTestsPassed);
	if (numTestsPassed == 3) {
		printf("  ***ALL GENRE MODIFICATION TESTS PASSED\n\n");
		return 1;
	}
	else {
		return 0;
	}
}

//test function for modifying rating
//returns 1 if *all* tests passed, 0 else
//also displays results of tests to console
int testDecreeDivineJudgment(void) {

	printf("\n  ***TESTING DECREE DIVINE JUDGMENT...\n");

	//setting up reference games and genre nodes
	Game testGame1 = { "Cow Simulator", "TastyMoo Corp", NULL,
	{ 3, 5 }, 5, 6 };
	Game refGame1 = { "Cow Simulator", "TastyMoo Corp", NULL,
	{ 3, 5 }, 5, 6 };
	int numTestsPassed = 0;

	//testing setting rating to illegal value outside [1,6]
	printf("Testing modifying rating to illegal value...");
	decreeDivineJudgment(&testGame1, 0);
	if (compareGames(testGame1, refGame1)) {
		printf("PASSED\n\n");
		numTestsPassed++;
	}
	else {
		printf("FAILED\n\n");
	}

	//testing setting rating to legal value inside [1,6]
	printf("Testing modifying rating to legal value...\n");
	decreeDivineJudgment(&testGame1, 3);
	refGame1.rating = 3;
	if (compareGames(testGame1, refGame1)) {
		printf("PASSED\n");
		numTestsPassed++;
	}
	else {
		printf("FAILED\n");
	}
	printf("\n%d of 2 decree tests passed\n", numTestsPassed);
	if (numTestsPassed == 2) {
		printf("  ***ALL DECREE JUDGMENT TESTS PASSED\n\n");
		return 1;
	}
	else {
		return 0;
	}
}

//test function for adding a new game to front of game list
//returns 1 if all tests passed, 0 else
//also displays results of tests to console
int testInsertGameAtFront(void) {
	printf("  ***TESTING INSERTING GAME AT FRONT OF LIST...\n");
	Game testGame1 = { "Cow Simulator", "TastyMoo Corp", NULL,
	{ 3, 5 }, 5, 6 };
	Game testGame2 = { "Kitty's Terror Spree", "Nefarious Kitty Ltd.", NULL,
	{ 9, 40 }, 13, 5 };

	GameNode * pTestHead = NULL;
	GameNode * pCurr = NULL;
	GameNode * pNext = NULL;
	int i = 0;
	int numTestsPassed = 0;
	
	//testing inserting at front of an empty list
	printf("Testing insertion at front of empty list...  ");
	insertGameAtFront(&pTestHead, testGame1);
	pCurr = pTestHead;
	i += compareGames(testGame1, pCurr->targetGame);
	//pointer check
	if (pCurr->pNext == NULL && pCurr->pPrev == NULL) {
		i++;
	}
	if (i == 2) {
		printf("\nPASSED\n\n");
		numTestsPassed++;
	}
	else {
		printf("\nFAILED\n\n");
	}

	//testing insertion at front of nonempty list
	printf("Testing insertion at front of nonempty list...  ");
	i = 0;
	insertGameAtFront(&pTestHead, testGame2);
	pCurr = pTestHead;
	
	if (compareGames(testGame2, pCurr->targetGame) && pCurr->pPrev == NULL) {
		i++;
	}
	pNext = pCurr->pNext;
	//make sure that the next node's pointers point to the right locations
	if (pNext->pNext == NULL && pNext->pPrev == pCurr) {
		i++;
	}
	if (compareGames(testGame1, pNext->targetGame)) {
		i++;
	}

	if (i == 3) {
		printf("\nPASSED\n\n");
		numTestsPassed++;
	}
	else {
		printf("\nFAILED\n\n");
	}

	//we don't leak memory in this household
	deleteGameList(&pTestHead);

	printf("%d of 2 insertion tests passed\n", numTestsPassed);
	if (numTestsPassed == 2) {
		printf("  ***ALL INSERTION TESTS PASSED\n\n");
		return 1;
	}
	else {
		return 0;
	}
}

//test function for removeSelectedGame,
//which is the core function for banish the exile
//returns 1 if all tests passed, 0 else
//also displays results of tests to console
int testRemoveSelectedGame(void) {
	printf("  ***TESTING REMOVING SELECTED GAME...\n\n");
	//setting up reference games and genre nodes
	Game testGame1 = { "Cow Simulator", "TastyMoo Corp", NULL,
	{ 3, 5 }, 5, 6 };
	Game testGame2 = { "Kitty's Terror Spree", "Nefarious Kitty Ltd.", NULL,
	{ 9, 40 }, 13, 5 };
	Game testGame3 = { "Beef Cooking Simulator", "TastyMoo Corp", NULL,
	{ 1, 23 }, 99, 4 };
	Game testGame4 = { "Dark Souls 638", "Form Hardware", NULL,
	{ 587, 45 }, 166, 2 };

	GenreNode * pTestGame1Genres = NULL;
	GenreNode * pTestGame2Genres = NULL;
	GenreNode * pTestGame3Genres = NULL;
	GenreNode * pTestGame4Genres = NULL;

	insertGenreAtFront(&pTestGame4Genres, "Story-Rich");
	insertGenreAtFront(&pTestGame4Genres, "YOU DIED");
	insertGenreAtFront(&pTestGame3Genres, "RTS");
	insertGenreAtFront(&pTestGame3Genres, "Story-Rich");
	insertGenreAtFront(&pTestGame2Genres, "Adventure");
	insertGenreAtFront(&pTestGame2Genres, "Action");
	insertGenreAtFront(&pTestGame2Genres, "Kitties");
	insertGenreAtFront(&pTestGame1Genres, "Violent");
	insertGenreAtFront(&pTestGame1Genres, "RPG");

	testGame1.pGenres = pTestGame1Genres;
	testGame2.pGenres = pTestGame2Genres;
	testGame3.pGenres = pTestGame3Genres;
	testGame4.pGenres = pTestGame4Genres;

	GameNode * pRefState1 = NULL;
	GameNode * pRefState2 = NULL;
	GameNode * pRefState3 = NULL;
	GameNode * pTestList = NULL;

	insertGameAtFront(&pTestList, testGame4);
	insertGameAtFront(&pTestList, testGame3);
	insertGameAtFront(&pTestList, testGame2);
	insertGameAtFront(&pTestList, testGame1);

	//testing phase starts here
	int numTestsPassed = 0;

	//test deletion in middle
	//set up refState1
	insertGameAtFront(&pRefState1, testGame4);
	insertGameAtFront(&pRefState1, testGame2);
	insertGameAtFront(&pRefState1, testGame1);

	printf("Testing deletion from middle of list...\n");
	removeSelectedGame(&pTestList, "Beef Cooking Simulator");

	if (compareGameLists(pTestList, pRefState1)) {
		printf("PASSED\n\n");
		numTestsPassed++;
	}
	else {
		printf("FAILED\n\n");
	}

	//test deletion of element that is not found
	printf("Testing deletion of invalid element...\n");
	removeSelectedGame(&pTestList, "Beef Cooking Simulator");

	if (compareGameLists(pTestList, pRefState1)) {
		printf("PASSED\n\n");
		numTestsPassed++;
	}
	else {
		printf("FAILED\n\n");
	}

	//test deletion at end
	//set up refState2
	insertGameAtFront(&pRefState2, testGame2);
	insertGameAtFront(&pRefState2, testGame1);
	printf("Testing deletion from end of list...\n");
	removeSelectedGame(&pTestList, "Dark Souls 638");

	if (compareGameLists(pTestList, pRefState2)) {
		printf("PASSED\n\n");
		numTestsPassed++;
	}
	else {
		printf("FAILED\n\n");
	}

	//test deletion at beginning
	//set up refState3
	insertGameAtFront(&pRefState3, testGame2);
	printf("Testing deletion from front of list...\n");
	removeSelectedGame(&pTestList, "Cow Simulator");

	if (compareGameLists(pTestList, pRefState3)) {
		printf("PASSED\n\n");
		numTestsPassed++;
	}
	else {
		printf("FAILED\n\n");
	}

	//test deletion of last element
	printf("Testing deletion of only element in list...\n");
	removeSelectedGame(&pTestList, "Kitty's Terror Spree");

	if (pTestList == NULL) {
		printf("PASSED\n\n");
		numTestsPassed++;
	}
	else {
		printf("FAILED\n\n");
	}

	//test attempted deletion from an empty list
	printf("Testing deletion from empty list...\n");
	removeSelectedGame(&pTestList, "Kitty's Terror Spree");

	if (pTestList == NULL) {
		printf("PASSED\n\n");
		numTestsPassed++;
	}
	else {
		printf("FAILED\n\n");
	}

	//memory cleanup
	deleteGenreList(&pTestGame1Genres);
	deleteGenreList(&pTestGame2Genres);
	deleteGenreList(&pTestGame3Genres);
	deleteGenreList(&pTestGame4Genres);

	deleteGameList(&pRefState1);
	deleteGameList(&pRefState2);
	deleteGameList(&pRefState3);
	deleteGameList(&pTestList);

	printf("%d of 6 deletion tests passed\n", numTestsPassed);
	if (numTestsPassed == 6) {
		printf("  ***ALL DELETION TESTS PASSED\n\n");
		return 1;
	}
	else {
		return 0;
	}
}

//test function for organizingTroops
//returns 1 if all tests passed, 0 else
//also displays results of tests to console
int testOrganizingTroops(void) {
	printf("  ***TESTING ORGANIZING TROOPS...\n\n");
	//setting up reference games and genre nodes
	Game testGame1 = { "A", "TastyMoo Corp", NULL,
	{ 3, 5 }, 5, 6 };
	Game testGame2 = { "B", "Nefarious Kitty Ltd.", NULL,
	{ 9, 40 }, 13, 5 };
	Game testGame3 = { "C", "TastyMoo Corp", NULL,
	{ 1, 23 }, 99, 4 };
	Game testGame4 = { "D", "Form Hardware", NULL,
	{ 587, 45 }, 166, 2 };

	int numTestsPassed = 0;
	GameNode * pTestList = NULL;

	//testing sorting an empty list
	printf("Testing sorting of empty list...\n");
	organizingTroops(&pTestList);
	if (pTestList == NULL) {
		numTestsPassed++;
		printf("PASSED\n\n");
	}
	else {
		printf("FAILED\n\n");
	}

	//testing sorting a list with a single element
	printf("Testing sorting of list with single element...\n");
	insertGameAtFront(&pTestList, testGame2);
	GameNode * pRefState1 = NULL;
	insertGameAtFront(&pRefState1, testGame2);
	
	organizingTroops(&pTestList);
	if (compareGameLists(pTestList, pRefState1)) {
		numTestsPassed++;
		printf("PASSED\n\n");
	}
	else {
		printf("FAILED\n\n");
	}

	//test of two elements
	printf("Testing sorting of list with two elements...\n");
	insertGameAtFront(&pTestList, testGame4);
	GameNode * pRefState2 = NULL;
	insertGameAtFront(&pRefState2, testGame4);
	insertGameAtFront(&pRefState2, testGame2);

	organizingTroops(&pTestList);
	if (compareGameLists(pTestList, pRefState2)) {
		numTestsPassed++;
		printf("PASSED\n\n");
	}
	else {
		printf("FAILED\n\n");
	}

	//test of four elements
	printf("Testing sorting general list...\n");
	deleteGameList(&pTestList);
	insertGameAtFront(&pTestList, testGame3);
	insertGameAtFront(&pTestList, testGame1);
	insertGameAtFront(&pTestList, testGame2);
	insertGameAtFront(&pTestList, testGame4);
	GameNode * pRefState3 = NULL;
	insertGameAtFront(&pRefState3, testGame4);
	insertGameAtFront(&pRefState3, testGame3);
	insertGameAtFront(&pRefState3, testGame2);
	insertGameAtFront(&pRefState3, testGame1);
	organizingTroops(&pTestList);
	if (compareGameLists(pTestList, pRefState3)) {
		numTestsPassed++;
		printf("PASSED\n\n");
	}
	else {
		printf("FAILED\n\n");
	}

	//testing list with no swaps necessary
	printf("Testing sorting list with all elements already in order...\n");
	deleteGameList(&pTestList);
	insertGameAtFront(&pTestList, testGame4);
	insertGameAtFront(&pTestList, testGame3);
	insertGameAtFront(&pTestList, testGame2);
	insertGameAtFront(&pTestList, testGame1);
	organizingTroops(&pTestList);
	if (compareGameLists(pTestList, pRefState3)) {
		numTestsPassed++;
		printf("PASSED\n\n");
	}
	else {
		printf("FAILED\n\n");
	}

	//memory cleanup
	deleteGameList(&pTestList);
	deleteGameList(&pRefState1);
	deleteGameList(&pRefState2);
	deleteGameList(&pRefState3);

	printf("%d of 5 sorting tests passed\n", numTestsPassed);
	if (numTestsPassed == 5) {
		printf("  ***ALL SORTING TESTS PASSED\n\n");
		return 1;
	}
	else {
		return 0;
	}
}
