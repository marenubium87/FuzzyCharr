//header file for CS122 PA2

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <Windows.h>
#include "sastrugagenres.h"

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

//allocates space on the heap for a new Node and initializes
//Node with information found in targetGame
//returns address of Node on the heap
GameNode * makeGame(Game targetGame);