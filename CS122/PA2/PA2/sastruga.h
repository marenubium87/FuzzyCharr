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

//displays all games with minimim rating >= minGameRating in 
//game list pointed to by pGameHead to the console
void printGameList(GameNode * pGameHead, int minGameRating);

//wrapper function to do menu option 3 from the main menu
void unveilForgottenRecordsWrapper(GameNode * pGameHead);

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

//stores all games in list pointed to by pGameHead to the outfile in csv format
void preserveSacredTeachings(GameNode * pGameHead, FILE * outfile);

//aux function for rewriteStoneTablets (modifying game)
//search for and lists all games corresponding to a particular developer
//stores the search list into gameResultsArray and also displays to console
void searchDeveloper(GameNode * pGameHead, GameNode * gameResultsArray[]);

//prompts user for new rating clamped to [1,6] for targetGame
//and modifies rating accordingly
//also aux function for modifyGame
void decreeDivineJudgment(Game * targetGame, int newRating);

//aux function for rewriteStoneTablets
//does what it says on the tin
void modifyGame(Game * targetGame);

//modifies a field in a target game from game list based on user input
void rewriteStoneTablets(GameNode * pGameHead);

//aux function for embarkOnQuest
//simulates adding of playtime to the currently played game
void addPlaytime(Game * targetGame);

//function to "play" games in list order starting from user-selected game
//until end of list
void embarkOnQuest(GameNode * pGameHead);

//wrapper to ask user for identity of a new game
//and inserts it into the front of the game list
//remember to call *location* of pGameHead when calling
void collectNewArtifact(GameNode ** pGameList);

//aux function for banishing the exile
//searches pGameHead and returns the GameNode * containing
//targetGameString, or returns NULL if targetGameString not found
GameNode * searchGameList(GameNode * pGameHead, char * targetGameString);

//aux function for banishing the exile, handles search and removing
//target game from list pointed to by pGameList
//dependencies:  searchGameList
void removeSelectedGame(GameNode ** pGameList, char * targetGameString);

//wrapper to prompt user to remove a game from the list
//remember to call *location* of pGameHead when calling
void banishExile(GameNode ** pGameList);

//aux function for organizing the troops, e.g. sorting
//swaps the pointers such that the positions of
//pTarget and the node immediately following it are swapped
//warning:  pass in the *location* of pGameList!
//warning:  do not call this function if either
//pTarget or pTarget->pNext are NULL
void swapElements(GameNode ** pGameList, GameNode * pTarget);

//sorts pGameList by title using ascii sorting
//remember to pass in *location* of pGameList when calling
void organizingTroops(GameNode ** pGameList);

//randomizes the order of element values in target int array
//akin to shuffle feature on music player
//aux function for openGatesofChaos
void randomizeArray(int * target, int targetSize);

//shuffle feature
void openGatesOfChaos(GameNode * pGameHead);