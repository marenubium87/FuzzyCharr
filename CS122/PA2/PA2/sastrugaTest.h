//header file for test functions

#define NUM_GENRES 8

#include "sastruga.h"

//wrapper to run all tests
void testWrapper(void);

//aux function for other tests
//deletes target genre list in the correct way by freeing memory and resetting
//pointer to NULL
void deleteList(GenreNode ** pGenreList);

//aux function for other tests
//returns 1 if the two genre lists are identical in entries and order, 0 else
int compareGenreLists(GenreNode * genreList1, GenreNode * genreList2);

//aux function for other tests
//returns 1 if game1's fields match game2's fields perfectly, 0 else
//dependencies:  compareGenreLists
int compareGames(Game game1, Game game2);

//aux function for other tests
//returns 1 if pGameList1's entries all match pGameList2's entries, 0 else
//NOTE this function will return 0 if both lists have the same games,
//but in a different order!
//dependencies:  compareGames
int compareGameLists(GameNode * gameList1, GameNode * gameList2);

//test function for loading game library from file
//returns 1 if test passed, 0 else
int testLoadGameLibrary(GameNode * pRefGameHead);