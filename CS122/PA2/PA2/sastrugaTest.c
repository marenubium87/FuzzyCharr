//source file for sastruga test functions

#include "sastrugaTest.h"

//wrapper to run all tests
void testWrapper(void) {

	//setting up reference games and genre nodes
	Game testGame1 = { "Cow Simulator", "IamMoo Productions", NULL,
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

	//tests start here
	GameNode * pRefGameList = NULL;
	insertGameAtFront(&pRefGameList, testGame1);
	insertGameAtFront(&pRefGameList, testGame2);
	insertGameAtFront(&pRefGameList, testGame3);
	insertGameAtFront(&pRefGameList, testGame4);

	printf("Testing loading games from file...  ");
	if (testLoadGameLibrary(pRefGameList)) {
		printf("PASSED\n");
	}
	else {
		printf("FAILED\n");
	}


	system("pause");

	deleteList(&pTestGame1Genres);
	deleteList(&pTestGame2Genres);
	deleteList(&pTestGame3Genres);
	deleteList(&pTestGame4Genres);
}

//aux function for other tests
//deletes target genre list in the correct way by freeing memory and resetting
//pointer to NULL
void deleteList(GenreNode ** pGenreList) {
	GenreNode * pTemp = NULL;
	while (*pGenreList != NULL) {
		//deletes first element repeatedly
		pTemp = *pGenreList;
		*pGenreList = pTemp->pNext;
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
int testLoadGameLibrary(GameNode * pRefGameHead) {
	
	FILE * infile = fopen("testInput.csv", "r");

	GameNode * pTestGameHead = NULL;
	loadGameLibrary(&pTestGameHead, infile);

	return compareGameLists(pTestGameHead, pRefGameHead);
}