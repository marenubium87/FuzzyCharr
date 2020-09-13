//source file for battleship
#include "battleship.h"

//end of program cleanup
void EoPCleanup(void) {
	printf("End of program; press enter to continue.");
	char tempCharr = '\0';
	scanf("%c", &tempCharr);
	scanf("%c", &tempCharr);
}

//initializes square target game board with dimensions [GRID_SIDE_LEN]
//and fills all entries with the EMPTY symbol
void initializeBoard(char target[][GRID_SIDE_LEN]) {
	for (int i = 0; i < GRID_SIDE_LEN; i++) {
		for (int j = 0; j < GRID_SIDE_LEN; j++) {
			target[i][j] = EMPTY;
		}
	}
}

//displays the target game board
//trueSight is a bool;	1 means ships, hits, misses can be seen
//						0 means only hits and misses can be seen
//if playerFlag = 1, prints YOUR BOARD as heading
//if playerFlag = 2, prints MY BOARD as heading
void displayBoard(char target[][GRID_SIDE_LEN], int playerFlag, int trueSight) {
	
	//prints board title
	if (playerFlag == 1) {
		printf("   ** YOUR BOARD ** \n\n");
	}
	else if (playerFlag == 2) {
		printf("    ** MY BOARD **\n\n");
	}
	
	//print column headings
	printf("   ");
	for (int k = 0; k < GRID_SIDE_LEN; k++) {
		printf("%d ", k);
	}
	printf("\n\n");
	
	//print everything else

	//if trueSight is on, print everything as normal
	if (trueSight == 1) {
		for (int i = 0; i < GRID_SIDE_LEN; i++) {
			printf("%d  ", i);
			for (int j = 0; j < GRID_SIDE_LEN; j++) {
				printf("%c ", target[i][j]);
			}
			printf("\n");
		}
	}

	//if trueSight is off, print hits and misses as is
	//otherwise, print the empty symbol for everything else
	else if (trueSight == 0) {
		for (int i = 0; i < GRID_SIDE_LEN; i++) {
			printf("%d  ", i);
			for (int j = 0; j < GRID_SIDE_LEN; j++) {
				if (target[i][j] == HIT || target[i][j] == MISS) {
					printf("%c ", target[i][j]);
				}
				else {
					printf("%c ", EMPTY);
				}
			}
			printf("\n");
		}
	}
}

//prompts user for a simulated coin flip and
//if the user guesses the correct side of coin and thus goes first, return 1
//if user guesses wrong and the AI will go first, return 2
int assignFirstMove(FILE * outfile) {
	
	system("cls");
	//gets player guess
	printf("\nHey, let's flip a coin to see who goes first!\n");
	printf("Type 1 for heads or 0 for tails:  ");
	fprintf(outfile, "Flipping a coin to determine starting player.\n\n");
	int PlayerGuess = 0;
	scanf("%d", &PlayerGuess);
	
	//announces player guess and also prints result to outfile
	if (PlayerGuess) {
		printf("\nYou called heads!\n\n");
		fprintf(outfile, "Player 1 calls heads.\n");

	}
	else {
		printf("\nYou called tails!\n\n");
		fprintf(outfile, "Player 1 calls tails.\n");
	}
	
	//makes actual flip.. 
	int actualFlip = 0;
	actualFlip = (rand() % 2);
	
	//and checks whether it's equal or not to player guess
	//also prints results to outfile.
	if (actualFlip == 1) {
		printf("   ...the flip is heads!\n\n");
		fprintf(outfile, "  ...and the flip is heads!\n");
	}
	else {
		printf("   ...the flip is tails!\n\n");
		fprintf(outfile, "  ...and the flip is tails!\n");
	}
	
	//tells player if they will go first and returns appropriate value
	//also reports results to outfile.
	char tempCharr = '\0';
	if (PlayerGuess == actualFlip) {
		fprintf(outfile, "\tPlayer 1 wins the toss and will go first.\n\n");
		printf("Fine, you go first.\n");
		printf("Press enter to continue.\n\n");
		scanf("%c", &tempCharr);
		scanf("%c", &tempCharr);
		return 1;
	}
	else {
		fprintf(outfile, "\tPlayer 2 wins the toss and will go first.\n\n");
		printf("Ha, I go first!\n");
		printf("Press enter to continue.\n\n");
		scanf("%c", &tempCharr);
		scanf("%c", &tempCharr);
		return 2;
	}
}

//auxiliary function required for manualShipPlacement and randomShipPlacement
//checks whether targetShip placed with either leftmost or uppermost coords
//at row, col on the targetBoard and
//placement in direction dir can be placed there
//returns 1 if placement is fine, 0 otherwise
int checkValidPlacement(char targetBoard[][GRID_SIDE_LEN], Ship targetShip, 
	int row, int col, char dir) {

	//checks for placement if ship is pointing to the right
	if (dir == 'r') {
		
		//checks for placements out of bounds
		//-1 has to do with the fact target ship occupies the (r, c) location
		//and thus extends one less to the right/down than it otherwise would
		if (col + targetShip.shipSize - 1 >= GRID_SIDE_LEN) {
			return 0;
		}

		//if ship isn't out of bounds, check if it overlaps w/ another ship
		for (int j = col; j < col + targetShip.shipSize; j++) {
			if (targetBoard[row][j] != EMPTY) {
				return 0;
			}
		}
	}

	//checks for placement if ship is pointing down
	if (dir == 'd') {

		//checks for placements out of bounds
		//-1 has to do with the fact target ship occupies the (r, c) location
		//and thus extends one less to the right/down than it otherwise would
		if (row + targetShip.shipSize - 1 >= GRID_SIDE_LEN) {
			return 0;
		}

		//if ship isn't out of bounds, check if it overlaps w/ another ship
		for (int i = row; i < row + targetShip.shipSize; i++) {
			if (targetBoard[i][col] != EMPTY) {
				return 0;
			}
		}
	}
	
	//if all checks passed, ship placement is okay
	return 1;
}

//manually places player ships from the first half of shipArray
//onto targetBoard, and checks for valid placement.
//also displays the grid after every placement.
//dependencies:  checkValidPlacement, displayBoard
//writes position of player's fleet to outfile
void manualShipPlacement(char targetBoard[][GRID_SIDE_LEN], 
	Ship shipArray[], FILE * outfile) {
	
	//player has half the total ships in shipArray
	int numPlayerShips = NUM_SHIPS / 2;
	int row = 0;
	int col = 0;
	int placementFlag = 0;
	char dir = '\0';

	fprintf(outfile, "Player one placing fleet...\n\n");

	for (int i = 0; i < numPlayerShips; i++) {
		
		

		//prompt user to place next ship, repeat as necessary
		//until they input a valid location and orientation.
		do {
			
			system("cls");
			
			//for manual ship placement, playerID is always 1
			//and trueSight is always on
			displayBoard(targetBoard, 1, 1);
			printf("\n\nPlace your %s using\n", shipArray[i].shipType);
			printf("two integers representing the row and column\n");
			printf("coordinates of where the start of the ship should\n");
			printf("be placed, followed by 'd' for if the ship should be\n");
			printf("oriented downward, or 'r' if the ship should be\n");
			printf("oriented rightward from the starting location.\n\n");
			printf("(Example input:  5 3 r )\n\n");
			scanf(" %d%d %c", &row, &col, &dir);
			
			//check if placement is okay
			placementFlag = 
				checkValidPlacement(targetBoard, shipArray[i], row, col, dir);
			
			//if placement is invalid, warn user
			if (!placementFlag) {
				printf("\nInvalid placement location.  ");
				printf("Press Enter to try again...\n");
				char tempCharr = '\0';
				scanf("%c", &tempCharr);
				scanf("%c", &tempCharr);
			}
		} while (!placementFlag);
		
		//if placement location is okay, place the ship
		//the starting column is relevant if the ship is placed horizontally
		//the starting row is relevant if the ship is placed vertically
		int start = 0;
		if (dir == 'r') {
			start = col;
		}
		else if (dir == 'd') {
			start = row;
		}

		//place number of symbols corresponding to shipSize
		//in the appropriate orientation, with the correct starting location
		for (int j = start; j < start + shipArray[i].shipSize; j++) {
			
			//if ship is placed horizontally, increment column
			if (dir == 'r') {
				targetBoard[row][j] = shipArray[i].symbol;
			}

			//if ship is placed vertically, increment row
			else if (dir == 'd') {
				targetBoard[j][col] = shipArray[i].symbol;
			}
		}

		//print ship location to outfile... since this function is for
		//player 1 only... we can hardcode that this will be player one
		fprintf(outfile, "\tPlayer 1 places %s at row %d, column %d, facing ",
			shipArray[i].shipType, row, col);
		if (dir == 'r') {
			fprintf(outfile, "right.\n");
		}
		else if (dir == 'd') {
			fprintf(outfile, "down.\n");
		}
	}

	//print board one last time when ship placement complete
	system("cls");
	displayBoard(targetBoard, 1, 1);
	printf("\n\nShip placement complete.  Press enter to continue.\n\n");
	fprintf(outfile, "\n\t**Player 1 ship placement complete.\n\n");
	char tempCharr = '\0';
	scanf("%c", &tempCharr);
	scanf("%c", &tempCharr);
}

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
	int playerFlag, int trueSight, FILE * outfile) {
	
	//each player has half the total ships in shipArray
	int numPlayerShips = NUM_SHIPS / 2;
	int row = 0;
	int col = 0;
	int placementFlag = 0;
	char dir = '\0';

	fprintf(outfile, "Player %d placing fleet...\n\n", playerFlag);

	//AI ships start at the back half of the array.
	int shipArrayStart = 0;
	if (playerFlag == 2) {
		shipArrayStart += numPlayerShips;
	}

	//determines whether we'll have truesight or not... player board
	//always gets truesight, computer board depends on the input value
	int playerTrueSight = 1;
	if (playerFlag == 2) {
		playerTrueSight = trueSight;
	}

	//display initial(empty) board.
	system("cls");
	if (playerFlag == 1) {
		printf("Placing your ships...\n\n");
	}
	else if (playerFlag == 2) {
		printf("Placing my ships...\n\n");
	}
	displayBoard(targetBoard, playerFlag, playerTrueSight);
	
	//place ships
	for (int i = shipArrayStart; i < shipArrayStart + numPlayerShips; i++) {
		do {
			//generate two coordinates and a direction, and see if
			//the next ship can be placed there.
			row = rand() % GRID_SIDE_LEN;
			col = rand() % GRID_SIDE_LEN;
			if (rand() % 2 == 1) {
				dir = 'r';
			}
			else {
				dir = 'd';
			}
			
			//if that location and orientation don't work, do it again.
			placementFlag =
				checkValidPlacement(targetBoard, shipArray[i], row, col, dir);
		} while (!placementFlag);

		//prints the first part of the "Placing..." message
		//with the correct ship type read from array
		system("cls");
		if (playerFlag == 1) {
			printf("Placing your ships...\n\n");
		}
		else if (playerFlag == 2) {
			printf("Placing my ships...\n\n");
		}
		displayBoard(targetBoard, playerFlag, playerTrueSight);
		printf("\nPlacing %s...  ", shipArray[i].shipType);
		Sleep(2400);
		
		//if placement location is okay, place the ship
		//the starting column is relevant if the ship is placed horizontally
		//the starting row is relevant if the ship is placed vertically
		int start = 0;
		if (dir == 'r') {
			start = col;
		}
		else if (dir == 'd') {
			start = row;
		}

		for (int j = start; j < start + shipArray[i].shipSize; j++) {
			//if ship is placed horizontally, increment column
			if (dir == 'r') {
				targetBoard[row][j] = shipArray[i].symbol;
			}
			//if ship is placed vertically, increment row
			else if (dir == 'd') {
				targetBoard[j][col] = shipArray[i].symbol;
			}
		}

		//print ship location to outfile for each ship...
		fprintf(outfile, "\tPlayer %d places %s at row %d, column %d, facing ",
			playerFlag, shipArray[i].shipType, row, col);
		if (dir == 'r') {
			fprintf(outfile, "right.\n");
		}
		else if (dir == 'd') {
			fprintf(outfile, "down.\n");
		}

		//updates display of board after placement
		//and second part of "placing..." message (the "done" part)
		system("cls");
		if (playerFlag == 1) {
			printf("Placing your ships...\n\n");
		}
		else if (playerFlag == 2) {
			printf("Placing my ships...\n\n");
		}

		displayBoard(targetBoard, playerFlag, playerTrueSight);
		printf("\nPlacing %s...  done.", shipArray[i].shipType);
		Sleep(1700);
	}

	//after all ships are placed, print this message
	printf("\n\nShip placement complete.  Press enter to continue.\n");
	fprintf(outfile, "\n\t**Player %d ship placement complete.\n\n", playerFlag);
	char tempCharr = '\0';
	scanf("%c", &tempCharr);
	scanf("%c", &tempCharr);
}

//gets player guess and has as its output parameters the row
//and column values of the player's guess.
void getPlayerGuess(int * rowGuess, int * colGuess) {
	printf("\nEnter the row and column you want to fire at,\n");
	printf("separated by a space, then press enter.  ");
	scanf("%d", rowGuess);
	scanf("%d", colGuess);
	//eats the enter
	char tempCharr = '\0';
	scanf("%c", &tempCharr);
}

//literally just generates two random numbers 0 - GRID_SIDE_LEN for both row and col
//and returns as output parameters
void getDumbAIGuess(int * rowGuess, int * colGuess) {
	*rowGuess = rand() % GRID_SIDE_LEN;
	*colGuess = rand() % GRID_SIDE_LEN;
}

//detects whether a salvo fired at coordinates rowGuess, colGuess
//onto targetBoard is a hit, a miss, or invalid.
//(e.g. is in a location that they've already fired on before
//returns 1 if hit, 0 if miss, -1 if location invalid
int hitDetection(char targetBoard[][GRID_SIDE_LEN], 
	int rowGuess, int colGuess) {

	//if location is already a hit or a miss, shot is invalid
	if (targetBoard[rowGuess][colGuess] == HIT ||
		targetBoard[rowGuess][colGuess] == MISS) {

		return -1;
	}
	//this is the miss scenario
	else if (targetBoard[rowGuess][colGuess] == EMPTY) {
		return 0;
	}
	//anything that's not covered is a hit at this point
	else {
		return 1;
	}
}

//run this function if the guess was a hit
//reads the symbol on targetBoard at rowGuess, colGuess
//and then updates info on that ship in shipArray
//targetPlayer is necessary to know which portion of shipArray to look
//if a ship sinks, return the index in shipArray for that ship, else return -1
//MUST run this fcn BEFORE turning that spot on targetBoard to the HIT symbol!
int updateStatusOnHit(char targetBoard[][GRID_SIDE_LEN], Ship shipArray[],
	int targetPlayer, int rowGuess, int colGuess) {

	//reads and saves symbol at the guess location
	char targetChar = targetBoard[rowGuess][colGuess];
	
	//sets start of array search location
	//if AI, start search at halfway through array
	int searchStart = 0;
	if (targetPlayer == 2) {
		searchStart = NUM_SHIPS / 2;
	}

	//cycle through all of target player's ships until finding the one
	//whose symbol matches, then update parameters re: that ship
	for (int i = searchStart; i < searchStart + NUM_SHIPS / 2; i++) {
		if (shipArray[i].symbol == targetChar) {
			shipArray[i].currentDamage++;

			//did the ship sink?  if so, flip the isSunk flag
			if (shipArray[i].currentDamage == shipArray[i].shipSize) {
				shipArray[i].isSunk = 1;
				return i;
			}
		}
	}

	//function runs through all of loop if no ship is sunk
	return -1;
}

//updates the targetBoard with the correct symbols on a hit or a miss.
void updateBoard(char targetBoard[][GRID_SIDE_LEN], 
	int rowGuess, int colGuess, int isHit) {

	if (isHit) {
		targetBoard[rowGuess][colGuess] = HIT;
	}
	else {
		targetBoard[rowGuess][colGuess] = MISS;
	}
}

//displays messages based on the player, if the shot was a hit or miss,
//and if a ship was sunk, the identity of the ship that was sunk.
//playerID is the acting/firing player
//also prints out results to outfile
void turnOutcomeMessage(Ship shipArray[], int playerID,
	int rowGuess, int colGuess, int isHit, int shipSunkIndex, FILE * outfile) {

	//if a ship was hit
	if (isHit) {
		printf("\nRow %d, column %d is a hit!\n\n", rowGuess, colGuess);

		//prints messages to log depending on which player did the hitting
		if (playerID == 1) {
			fprintf(outfile, " and scores a hit on player 2!\n");
		}
		else if (playerID == 2) {
			fprintf(outfile, " and scores a hit on player 1!\n");
		}


		//furthermore, did a ship sink?  if so, which one?
		if (shipSunkIndex > -1) {
			if (playerID == 1) {
				Sleep(1200);
				printf("Shit, you sank my %s!\n\n", 
					shipArray[shipSunkIndex].shipType);
				fprintf(outfile, "\t\t...player 2's %s is sunk!\n",
					shipArray[shipSunkIndex].shipType);
			}
			else if (playerID == 2) {
				Sleep(1200);
				printf("Ha, I sank your %s!\n\n", 
					shipArray[shipSunkIndex].shipType);
				fprintf(outfile, "\t\t...player 1's %s is sunk!\n",
					shipArray[shipSunkIndex].shipType);
			}
		}
		//if a ship was not hit
	}
	else {
		printf("\nRow %d, column %d is a miss!\n\n", rowGuess, colGuess);

		//prints log messages depending on acting player
		if (playerID == 1) {
			fprintf(outfile, " and misses player 2.\n");
		}
		else if (playerID == 2) {
			fprintf(outfile, " and misses player 1.\n");
		}

	}
}

//putting it all together, conducts a single turn for player 1
//depends on basically all of the other shit
void conductP1Turn(char player1Board[][GRID_SIDE_LEN],
	char player2Board[][GRID_SIDE_LEN], 
	Ship shipArray[], Stats statArray[], int trueSight, FILE * outfile) {

	//sets up containers for row guess and column guess,
	//hit detection, and whether a ship was sunk
	int rowGuess = -1;
	int colGuess = -1;
	int isHit = -1;
	int shipSunkIndex = -1;

	//clear screen and draw the boards...
	//player 2 board dependent on trueSight, player1 board always visible
	system("cls");
	displayBoard(player2Board, 2, trueSight);
	printf("\n------------------------\n\n");
	displayBoard(player1Board, 1, 1);
	printf("\n\n   ***YOUR MOVE***\n");

	//prompts player for a guess and validates, repeats if location invalid
	//and warns the user, and redraws the board
	do {
		getPlayerGuess(&rowGuess, &colGuess);
		isHit = hitDetection(player2Board, rowGuess, colGuess);
		if (isHit == -1) {
			system("cls");
			displayBoard(player2Board, 2, trueSight);
			printf("\n------------------------\n\n");
			displayBoard(player1Board, 1, 1);
			printf("\n\n   ***YOUR MOVE***\n");
			printf("\n%d, %d is not a valid location!", rowGuess, colGuess);
			printf("  Try again.\n\n");
		}
	} while (isHit == -1);

	//firing message here, before hit detection
	fprintf(outfile, "\tPlayer 1 fires into row %d, column %d...", 
		rowGuess, colGuess);

	//add 1 to the number of shots in stats
	statArray[0].numShots++;

	//if location is a hit, update shipArray... for player 1 turn,
	//targetPlayer is always 2
	//also update stats
	if (isHit) {
		shipSunkIndex = updateStatusOnHit(player2Board, shipArray, 2,
			rowGuess, colGuess);
		statArray[0].numHits++;
	}

	//update player 2's board with the shot
	updateBoard(player2Board, rowGuess, colGuess, isHit);

	//redraw the board, and print hit/miss and sink messages
	system("cls");
	displayBoard(player2Board, 2, trueSight);
	printf("\n------------------------\n\n");
	displayBoard(player1Board, 1, 1);
	printf("\n\n   ***YOUR MOVE***\n");
	turnOutcomeMessage(shipArray, 1, rowGuess, colGuess, 
		isHit, shipSunkIndex, outfile);
}

//conducts a single turn for player 2, the AI
void conductP2Turn(char player1Board[][GRID_SIDE_LEN],
	char player2Board[][GRID_SIDE_LEN],
	Ship shipArray[], Stats statArray[], int trueSight, FILE * outfile) {
	
	//sets up containers for row guess and column guess,
	//hit detection, and whether a ship was sunk
	int rowGuess = -1;
	int colGuess = -1;
	int isHit = -1;
	int shipSunkIndex = -1;

	//clear screen and draw the boards...
	//player 2 board dependent on trueSight, player1 board always visible
	system("cls");
	displayBoard(player2Board, 2, trueSight);
	printf("\n------------------------\n\n");
	displayBoard(player1Board, 1, 1);
	printf("\n\n   ***MY MOVE***\n");

	//guess a guess from the AI and prints out the AI's guess as a message.
	do {
		getDumbAIGuess(&rowGuess, &colGuess);
		isHit = hitDetection(player1Board, rowGuess, colGuess);
	} while (isHit == -1);

	printf("\nHmm... I guess: ");
	Sleep(1800);
	printf("row %d, column %d!", rowGuess, colGuess);
	Sleep(2400);

	//firing message for log
	fprintf(outfile, "\tPlayer 2 fires into row %d, column %d...",
		rowGuess, colGuess);

	//add 1 to the number of shots in stats
	statArray[1].numShots++;

	//if location is a hit, update shipArray... for player 2 turn,
	//targetPlayer is always 1
	//also updates number of hits in stats
	if (isHit) {
		shipSunkIndex = updateStatusOnHit(player1Board, shipArray, 1,
			rowGuess, colGuess);
		statArray[1].numHits++;
	}

	//update player 1's board with the shot
	updateBoard(player1Board, rowGuess, colGuess, isHit);

	//redraw the board, and print hit/miss and sink messages
	system("cls");
	displayBoard(player2Board, 2, trueSight);
	printf("\n------------------------\n\n");
	displayBoard(player1Board, 1, 1);
	printf("\n\n   ***MY MOVE***\n");

	//reprints the "I guess... message for continuity before the hit message
	printf("\nHmm... I guess: row %d, column %d!\n\n", rowGuess, colGuess);
	turnOutcomeMessage(shipArray, 2, rowGuess, colGuess, 
		isHit, shipSunkIndex, outfile);
}

//end of turn prompt
//returns 's' if user surrenders
char endOfTurnPrompt(int * trueSight) {
	printf("End of turn.  Press 'c' to continue,\n");
	printf("Press 's' to surrender, or 't' to toggle trueSight.  ");
	char userChoice = '\0';
	scanf(" %c", &userChoice);
	//toggles trueSight
	if (userChoice == 't') {
		if (*trueSight == 0) {
			(*trueSight)++;
		}
		else if (*trueSight == 1) {
			(*trueSight)--;
		}
	}
	return userChoice;
}

//does what it says
//figures out if all ships of the targetPlayer have sunk
//returns 1 if all ships are sunk, else returns 0
//also prints a message relevant to the situation if all ships sunk
//and prints that message to the log as well.
int allShipsSunk(int targetPlayer, Ship shipArray[], FILE * outfile) {

	//sets start of array search location
	//if AI, start search at halfway through array
	int searchStart = 0;
	if (targetPlayer == 2) {
		searchStart = NUM_SHIPS / 2;
	}
	
	//if any ships in the part of the array corresponding to 
	//target player haven't sunk, then obviously not all ships are sunk
	for (int i = searchStart; i < searchStart + NUM_SHIPS / 2; i++) {
		if (!shipArray[i].isSunk) {
			return 0;
		}
	}

	//if we make it through the loop without returning 0, then all ships
	//for targetPlayer have sunk.
	if (targetPlayer == 2) {
		Sleep(1200);
		printf("Shit, you've sunk all of my ships!\n\n");
		fprintf(outfile, "\n\t***All of player 2's ships have sunk!!");
	}
	else if (targetPlayer == 1) {
		Sleep(1200);
		printf("Ha, I've sunk all of your ships!\n\n");
		fprintf(outfile, "\n\t***All of player 1's ships have sunk!!");
	}
	return 1;
}

//called when player 1 or player 2 have won the game, and print out
//a relevant message when that happens.
//also writes it to the log.
void endOfGameMessage(int winPlayer, FILE * outfile) {
	if (winPlayer == 1) {
		Sleep(1200);
		printf("\nHmph... I guess you won, somehow.\n\n");
		fprintf(outfile, "\n\n\t***GAME OVER, PLAYER 1 VICTORY");
	}
	else if (winPlayer == 2) {
		Sleep(1200);
		printf("\nHa, suck it, I win!\n\n");
		fprintf(outfile, "\n\n\t***GAME OVER, PLAYER 2 VICTORY");
	}
}

//computes statistics and writes the final results to the outfile.
void writeStats(Stats playerStats[], FILE * outfile) {
	fprintf(outfile, "\n\n\n\t***STATISTICS***\n\n");

	int shotsMissed = 0;
	double percentAccuracy = 0.0;

	fprintf(outfile, "Statistics for Player 1:\n\n");
	
	//takes care of an edge condition when player 2 goes first
	//and player 1 surrenders before firing a single shot.
	if (playerStats[0].numShots == 0) {
		fprintf(outfile, "Player 1 did not fire any shots.\n");
	}
	//player 1 stats
	else {
		shotsMissed = playerStats[0].numShots - playerStats[0].numHits;
		percentAccuracy = (double)playerStats[0].numHits / 
			playerStats[0].numShots * 100;
		fprintf(outfile, "\tShots hit:  %d\n", playerStats[0].numHits);
		fprintf(outfile, "\tShots missed:  %d\n", shotsMissed);
		fprintf(outfile, "\tShots taken:  %d\n", playerStats[0].numShots);
		fprintf(outfile, "\n\tAccuracy: %4.1f%%\n", percentAccuracy);
	}

	//player 2 stats
	fprintf(outfile, "\n");
	fprintf(outfile, "Statistics for Player 2:\n\n");
	shotsMissed = playerStats[1].numShots - playerStats[1].numHits;
	percentAccuracy = (double)playerStats[1].numHits /
		playerStats[1].numShots * 100;
	fprintf(outfile, "\tShots hit:  %d\n", playerStats[1].numHits);
	fprintf(outfile, "\tShots missed:  %d\n", shotsMissed);
	fprintf(outfile, "\tShots taken:  %d\n", playerStats[1].numShots);
	fprintf(outfile, "\n\tAccuracy: %4.1f%%\n", percentAccuracy);

}

//wrapper to play all of battleship
//trueSight is a bool;	1 means ships, hits, misses can be seen on AI board
//						0 means only hits and misses can be seen on AI board
void playBattleship(int * trueSight) {
	
	//sets up the ship array in order player1, player2, and
	//in order carrier, battleship, destroyer, submarine, patrol boat
	//note player 1 has ship indices 0-4, player 2 has ship indices 5-9
	Ship shipArray[NUM_SHIPS] = {
		{ "carrier", 'c', 5, 0, 0 },
		{ "battleship", 'b', 4, 0, 0 },
		{ "cruiser", 'r', 3, 0, 0 },
		{ "submarine", 's', 2, 0, 0 },
		{ "patrol boat", 'p', 1, 0, 0 },
		{ "carrier", 'c', 5, 0, 0 },
		{ "battleship", 'b', 4, 0, 0 },
		{ "cruiser", 'r', 3, 0, 0 },
		{ "submarine", 's', 2, 0, 0 },
		{ "patrol boat", 'p', 1, 0, 0 }
	};

	//sets up the stats array for both players
	Stats playerStats[2] = { { 1, 5, 0, 0 },{ 2, 5, 0, 0 } };

	//opens logfile for writing
	FILE * outfile = NULL;
	outfile = fopen("battleship.log", "w");
	fprintf(outfile, "***START OF GAME***\n\n");

	//sets up both player boards and initializes them
	char player1Board[GRID_SIDE_LEN][GRID_SIDE_LEN] = { '\0' };
	char player2Board[GRID_SIDE_LEN][GRID_SIDE_LEN] = { '\0' };
	initializeBoard(player1Board);
	initializeBoard(player2Board);

	//see if player wants to place ships manually
	//if not, auto-place ships for player
	system("cls");
	printf("\nWelcome, commander!\n");
	printf("Do you wish to place your ships manually?\n");
	printf("(Enter y or n)  ");
	char manualShipPlacementResponse = '\0';
	scanf(" %c", &manualShipPlacementResponse);
	
	if (manualShipPlacementResponse == 'y') {
		manualShipPlacement(player1Board, shipArray, outfile);
	}
	else {
		autoShipPlacement(player1Board, shipArray, 1, 1, outfile);
	}

	//then auto-place ships for computer
	autoShipPlacement(player2Board, shipArray, 2, *trueSight, outfile);

	//flips a coin to see who goes first.
	int firstMove = assignFirstMove(outfile);

	//declare vars for userResponse and allShipsSunk, needed later
	char userResponse = '\0';
	int allShipsSunkFlag = 0;

	fprintf(outfile, "\n***START OF COMBAT***\n\n");

	//if computer wins, computer essentially takes an extra turn
	//before the player1 turn, player2 turn sequence
	if (firstMove == 2) {
		conductP2Turn(player1Board, player2Board, shipArray,
			playerStats, *trueSight, outfile);
		userResponse = endOfTurnPrompt(trueSight);
	}
	//print this if user is a coward and surrenders after the first AI turn.
	if (userResponse == 's') {
		endOfGameMessage(2, outfile);
		fprintf(outfile, "\n\t***Player 1 has surrendered!!");
	}

	//keep playing until all ships sunk for a player or user surrenders
	while (userResponse != 's' && !allShipsSunkFlag) {
		
		//player 1 turn
		conductP1Turn(player1Board, player2Board, shipArray,
			playerStats, *trueSight, outfile);
		
		//have all of player 2's ships sunk?
		allShipsSunkFlag = allShipsSunk(2, shipArray, outfile);
		
		//if not, print the end of turn prompt.
		if (!allShipsSunkFlag) {
			userResponse = endOfTurnPrompt(trueSight);
		}
		//otherwise, print the victory message for player 1
		else {
			endOfGameMessage(1, outfile);
		}

		//only do player 2's turn if user hasn't surrendered,
		//and if user hasn't sunk all of AI's ships
		if (userResponse != 's' && !allShipsSunkFlag) {
			
			//player 2 turn
			conductP2Turn(player1Board, player2Board, shipArray,
				playerStats, *trueSight, outfile);

			//have all of player 1's ships sunk?
			allShipsSunkFlag = allShipsSunk(1, shipArray, outfile);
			
			//if not, print the end of turn prompt.
			if (!allShipsSunkFlag) {
				userResponse = endOfTurnPrompt(trueSight);
			}
			//otherwise, print the victory message for player 2
			else {
				endOfGameMessage(2, outfile);
			}
		}

		//if player 1 surrendered, print victory message for player 2
		if (userResponse == 's') {
			fprintf(outfile, "\n\t***Player 1 has surrendered!!");
			endOfGameMessage(2, outfile);
		}
	}

	//computes statistics and writes the final results to the outfile.
	writeStats(playerStats, outfile);

	fprintf(outfile, "\n\n***END OF LOG FILE***");
	//closes logfile
	fclose(outfile);

	//prompts user to return to menu
	printf("Press Enter to return to the main menu.\n\n");
	char tempCharr = '\0';
	scanf("%c", &tempCharr);
	scanf("%c", &tempCharr);
}

//prints the main menu
void printMenu() {
	printf("Please choose from the following menu options:\n\n");
	printf(" 1.  About Battleship\n");
	printf(" 2.  About Prissy Kitty Productions\n");
	printf(" 3.  About trueSight(tm)\n");
	printf(" 4.  Play battleship\n");
	printf(" 5.  Quit\n\n");
}

//prints the text corresponding to menu option 1
void printAboutBattleship() {
	system("cls");
	printf("\nABOUT BATTLESHIP\n\n");
	printf("Battleships is... (sigh) y'know, just google the fucking rules.\n\n");
	printf("Press enter to return.\n\n");
	char tempCharr = '\0';
	scanf("%c", &tempCharr);
	scanf("%c", &tempCharr);
}

//prints the text corresponding to menu option 2
void printAboutCompany() {
	system("cls");
	printf("\nABOUT PRISSY KITTY PRODUCTIONS\n");
	printf("\nPrissy Kitty Productions (or PKP, if you prefer, but only if you don't\n");
	printf("value your life) is a subsidiary of the shadowy and nefarious\n");
	printf("Great Lynx Consortium.  Frankly, even by reading this about section\n");
	printf("you are putting your life at risk.  So... yeah...\n\n");
	printf("Use this program at your own risk.\n");
	printf("The developer of this program does not accept any liability for any losses\n");
	printf("or damages from the use of this program, including, but not limited to:\n\n");
	printf("*Fire\n");
	printf("*Loss of life and/or limb and/or navy\n");
	printf("*Having jackals consume the aformentioned life or limb\n");
	printf("*Acts of God (or Gods, if polytheistic)\n");
	printf("*A lot of glub glub\n");
	printf("*Dizziness\n");
	printf("*Calling this game \"battleshit\" instead\n\n");
	printf("If you experience an erection lasting longer than three hours while\n");
	printf("using this program, stop IMMEDIATELY, call your doctor, and brag.\n\n");
	printf("Press enter to return.\n\n");

	char tempCharr = '\0';
	scanf("%c", &tempCharr);
	scanf("%c", &tempCharr);
}

//prints text corresponding to menu option 3 and allows user
//to toggle trueSight from the main menu.
void printAboutTrueSight(int * trueSight) {
	char userInput = '\0';
	do {
		scanf("%c", &userInput);
		system("cls");
		printf("\nABOUT TRUESIGHT(tm)\n\n");
		printf("trueSight(tm) is a proprietary intellectual property\n");
		printf("copyrighted by the Great Lynx Consortium.\n");
		printf("When the mystical power of kitty trueSight(tm)\n");
		printf("is invoked, one will literally pierce the veil\n");
		printf("of the fog of war and be able to see the opponent's\n");
		printf("fleet as plain as day.\n\n");
		printf("WARNING:  trueSight(tm) has been known to cause cancer\n");
		printf("in laboratory animals in the state of California, but frankly,\n");
		printf("every fucking thing out there does.  Regardless,\n");
		printf("use trueSight(tm) at your own risk.\n\n");
		printf("The current status of true sight is:  ");
		
		if (*trueSight) {
			printf("ON\n\n");
		}
		else {
			printf("OFF\n\n");
		}
		
		printf("Press 'c' to continue, or 't' to toggle trueSight(tm).  ");
		scanf("%c", &userInput);
		if (userInput == 't') {
			if (*trueSight == 0) {
				(*trueSight)++;
			}
			else if (*trueSight == 1) {
				(*trueSight)--;
			}
		}
	} while (userInput == 't');
}