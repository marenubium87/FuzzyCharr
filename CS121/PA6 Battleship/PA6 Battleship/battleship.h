//header file for battleship

#define _CRT_SECURE_NO_WARNINGS
#define GRID_SIDE_LEN 10
#define NUM_SHIPS 10

//symbol definitions for use on game board
#define EMPTY '.'
#define HIT 'X'
#define MISS '='

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <stdbool.h>

//structure for saving player stats and also checking for win condition
//e.g. a player loses and the game ends when shipsAfloat goes to 0
typedef struct stats {
	int playerID;
	int shipsAfloat;
	int numShots;
	int numHits;
} Stats;


//ship types:  "carrier", "battleship", "cruiser", "destroyer", "patrol boat"
//symbols:  'c', 'b', 'r', 'd', 'p'
//ship sizes:  5, 4, 3, 3, 2 (size on board and also number of hits to sink)
typedef struct ship {
	char shipType[12];
	char symbol;
	int shipSize;
	int currentDamage;
	int isSunk;
} Ship;

//end of program cleanup
void EoPCleanup(void);

//initializes square target game board with dimensions [GRID_SIDE_LEN]
//and fills all entries with the EMPTY symbol
void initializeBoard(char target[][GRID_SIDE_LEN]);

//displays the target game board
//trueSight is a bool;	1 means ships, hits, misses can be seen
//						0 means only hits and misses can be seen
//if playerFlag = 1, prints YOUR BOARD as heading
//if playerFlag = 2, prints MY BOARD as heading
void displayBoard(char target[][GRID_SIDE_LEN], int playerFlag, int trueSight);

//prompts user for a simulated coin flip and if the user guesses
//the correct side of coin, return 1, else return 0
//also prints out the result of the coin flip to outfile.
int assignFirstMove(FILE * outfile);

//auxiliary function required for manualShipPlacement and randomShipPlacement
//checks whether targetShip placed with either leftmost or uppermost coords
//at row, col on the targetBoard and
//placement in direction dir can be placed there
//returns 1 if placement is fine, 0 otherwise
int checkValidPlacement(char targetBoard[][GRID_SIDE_LEN], Ship targetShip,
	int row, int col, char dir);

//manually places player ships from the first half of shipArray
//onto targetBoard, and checks for valid placement.
//also displays the grid after every placement.
//dependencies:  checkValidPlacement, displayBoard
//writes position of player's fleet to outfile
void manualShipPlacement(char targetBoard[][GRID_SIDE_LEN], 
	Ship shipArray[], FILE * outfile);

//randomly places player or computer ships from shipArray
//onto targetBoard, and checks for valid placement.
//if playerFlag = 1, places player ships from first half of shipArray
//if playerFlag = 2, places computer ships from second half of shipArray
//if truesight is on, displays ship locations for AI as well.
//writes position of target player's fleet to outfile
//trueSight is a bool;	1 means ships, hits, misses can be seen
//						0 means only hits and misses can be seen
//dependencies:  checkValidPlacement, displayBoard
void autoShipPlacement(char targetBoard[][GRID_SIDE_LEN], Ship shipArray[],
	int playerFlag, int trueSight, FILE * outfile);

//gets player guess and has as its output parameters the row
//and column values of the player's guess.
void getPlayerGuess(int * rowGuess, int * colGuess);

//literally just generates two random numbers 0-9 for both row and col
//and returns as output parameters
void getDumbAIGuess(int * rowGuess, int * colGuess);

//detects whether a salvo fired at coordinates rowGuess, colGuess
//onto targetBoard is a hit, a miss, or invalid.
//(e.g. is in a location that they've already fired on before
//returns 1 if hit, 0 if miss, -1 if location invalid
int hitDetection(char targetBoard[][GRID_SIDE_LEN],
	int rowGuess, int colGuess);

//run this function if the guess was a hit
//reads the symbol on targetBoard at rowGuess, colGuess
//and then updates info on that ship in shipArray
//targetPlayer is necessary to know which portion of shipArray to look
//if a ship sinks, return the index in shipArray for that ship, else return -1
//MUST run this fcn BEFORE turning that spot on targetBoard to the HIT symbol!
int updateStatusOnHit(char targetBoard[][GRID_SIDE_LEN], Ship shipArray[],
	int targetPlayer, int rowGuess, int colGuess);

//updates the targetBoard with the correct symbols on a hit or a miss.
void updateBoard(char targetBoard[][GRID_SIDE_LEN],
	int rowGuess, int colGuess, int isHit);

//displays messages based on the player, if the shot was a hit or miss,
//and if a ship was sunk, the identity of the ship that was sunk.
//playerID is the acting/firing player
//also prints out results to outfile
void turnOutcomeMessage(Ship shipArray[], int playerID,
	int rowGuess, int colGuess, int isHit, int shipSunkIndex, FILE * outfile);

//putting it all together, conducts a single turn for player 1
//depends on basically all of the other shit
void conductP1Turn(char player1Board[][GRID_SIDE_LEN],
	char player2Board[][GRID_SIDE_LEN],
	Ship shipArray[], Stats statArray[], int trueSight, FILE * outfile);

//conducts a single turn for player 2, the AI
void conductP2Turn(char player1Board[][GRID_SIDE_LEN],
	char player2Board[][GRID_SIDE_LEN],
	Ship shipArray[], Stats statArray[], int trueSight, FILE * outfile);

//end of turn prompt
//returns 's' if user surrenders
char endOfTurnPrompt(int * trueSight);

//does what it says
//figures out if all ships of the targetPlayer have sunk
//returns 1 if all ships are sunk, else returns 0
//also prints a message relevant to the situation if all ships sunk
//and prints that message to the log as well.
int allShipsSunk(int targetPlayer, Ship shipArray[], FILE * outfile);

//called when player 1 or player 2 have won the game, and print out
//a relevant message when that happens.
//also writes it to the log.
void endOfGameMessage(int winPlayer, FILE * outfile);

//computes statistics and writes the final results to the outfile.
void writeStats(Stats playerStats[], FILE * outfile);

//wrapper to play all of battleship
//trueSight is a bool;	1 means ships, hits, misses can be seen on AI board
//						0 means only hits and misses can be seen on AI board
void playBattleship(int * trueSight);

//prints the main menu
void printMenu();

//prints the text corresponding to menu option 1
void printAboutBattleship();

//prints the text corresponding to menu option 2
void printAboutCompany();

//prints text corresponding to menu option 3 and allows user
//to toggle trueSight from the main menu.
void printAboutTrueSight(int * trueSight);