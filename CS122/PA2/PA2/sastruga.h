//header file for CS122 PA2

#include "sastrugaGenres.h"

//playtime structure (h:m)
typedef struct playtime {
	int hours;
	int minutes;
} Playtime;

//game information structure
typedef struct game {
	char title[80];
	char developer[60];
	struct genreNode * pGenres;
	Playtime timePlayed;
	int numAchieves;
	int rating;
} Game;

//doubly linked list structure
typedef struct gameNode {
	Game targetGame;
	struct gameNode * pNext;
	struct gameNode * pPrev;
} GameNode;

//prints main Sastruga menu
void printMenu(void);

//displays all attributes of targetGame to the console
void displayGameContents(Game targetGame);

//displays game list pointed to by pGameHead to the console
void printGameList(GameNode * pGameHead);

//allocates space on the heap for a new Node and initializes
//Node with information found in targetGame
//returns address of Node on the heap
GameNode * makeGame(Game targetGame);

//inserts GameNode containing targetGame to front of game list
//remember to call *location* of pGameHead when calling
void insertGameAtFront(GameNode ** pGameList, Game targetGame);

//loads game library from infile via insert at front to list
//assumes infile already opened for read
void loadGameLibrary(GameNode ** pGameList, FILE * infile);