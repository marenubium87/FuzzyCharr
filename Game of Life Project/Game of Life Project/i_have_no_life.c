//Source file for Game of Life project

#include "i_have_no_life.h"

//end of program cleanup
void EoPCleanup(void) {
	printf("End of program, press enter to continue.\n\n");
	char tempCharr = '\0';
	scanf("%c", &tempCharr);
	scanf("%c", &tempCharr);
}

//prints out the life array to the console with window location and size
//determined by the constants in the header file
//NOTE: remember that the number of rows is actually related to HEIGHT constants
//		similarly, the number of columns is actually related to WIDTH constants
void printLifeGrid(char target[][NUM_COLS]) {
	for (int i = 0; i < VIEW_NUM_ROWS; i++) {
		
		for (int j = 0; j < VIEW_NUM_COLS; j++) {
			printf("%c ", target[i +	VIEW_ROW_OFFSET][j + VIEW_COL_OFFSET]);
		}
		printf("\n");
	}
}

//populates the life array with coordinates (number pairs)
//in the format R C (row, then column... not x,y!) from infile
void populateLifeGrid(FILE * infile, char target[][NUM_COLS]) {
	int tempRow = 0;
	int tempCol = 0;

	while (!feof(infile)) {
		//reads next two values and assigns to row and col
		fscanf(infile, "%d", &tempRow);
		fscanf(infile, "%d", &tempCol);
		//assigns the correct symbol onto the grid
		target[tempRow][tempCol] = ALIVE;
	}
	//assign all other cells to empty
	for (int i = 0; i < NUM_ROWS; i++) {

		for (int j = 0; j < NUM_COLS; j++) {
			
			if (target[i][j] == '\0') {
				target[i][j] = EMPTY;
			}
		}
	}
}

//returns the number of live cells in the Moore neighborhood (check wikipedia if you don't know)
//of the element at (rowIndex, colIndex), excluding the element itself.
int countAdjLiveCells(char target[][NUM_COLS], int rowIndex, int colIndex) {
	int aliveCount = 0;
	
	//check the row immediately before, on, and after the rowIndex-th row
	for (int i = -1; i <= 1; i++) {
		//but we can't have the indices be out of bounds, so.
		if ((rowIndex + i) > -1 && (rowIndex + i) < NUM_ROWS) {

			//and this is basically the exact same shit, only with the columns
			for (int j = -1; j <= 1; j++) {
				//and once again, we cannot have the indices out of bounds
				if ((colIndex + j) > -1 && (colIndex + j < NUM_COLS)) {

					//okay, so finally, whatever is here should be in bounds
					//then check if it's alive or dying (b/c still technically alive
					//in the current generation!!)
					if (target[rowIndex + i][colIndex + j] == ALIVE ||
						target[rowIndex + i][colIndex + j] == DYING)
					{
						//if it is alive, add 1 to the alive counter
						aliveCount++;
					}
				}
			}
		}
	}
	//however, if the element itself is alive, we cannot count that and must
	//reduce the counter by 1, since we only count cells in the Moore neighborhood.
	if (target[rowIndex][colIndex] == ALIVE || target[rowIndex][colIndex] == DYING) {
		aliveCount--;
	}

	//after all that, should have the correct count of adjacent cells that are alive.
	return aliveCount;
}

//updates the entire grid for one "half" iteration using the rules for game of life
//meaning that cells that are born are temporarily assigned the BIRTH symbol (see consts)
//and cells that are dying are temporarily assigned the DYING symbol (see consts)
//required for:  updateOneIteration
void updateOneHalfIteration(char target[][NUM_COLS]) {
	int adjLiveCells = 0;
	//cycle through all cells
	for (int i = 0; i < NUM_ROWS; i++) {
		for (int j = 0; j < NUM_COLS; j++) {
			//count the adjacent live cells to the currently selected cell, at row i col j
			adjLiveCells = countAdjLiveCells(target, i, j);

			//essentially game of life rules
			//live cells will die unless they have exactly 2 or 3 neighbors
			if (target[i][j] == ALIVE && (adjLiveCells < 2 || adjLiveCells > 3)) {
				target[i][j] = DYING;
			}
			//dead cells with exactly 3 live neighbors becomes alive
			if (target[i][j] == EMPTY && adjLiveCells == 3) {
				target[i][j] = BIRTH;
			}
		}
	}
}

//updates the entire grid for a full iteration using the rules for game of life
//essentially doing the half iteration, then going through the grid again and
//assigning BIRTH symbols to ALIVE; DYING symbols to EMPTY
//dependencies: updateOneHalfIteration, for some unknown reason /s
void updateOneIteration(char target[][NUM_COLS]) {	
	//do the half iteration first
	updateOneHalfIteration(target);
	for (int i = 0; i < NUM_ROWS; i++) {
		for (int j = 0; j < NUM_COLS; j++) {
			if (target[i][j] == BIRTH) {
				target[i][j] = ALIVE;
			}
			if (target[i][j] == DYING) {
				target[i][j] = EMPTY;
			}
		}
	}
}

//counts the number of cells that are alive at any given point.
//will only count cells marked with ALIVE symbol; will not count birthing or dying cells.
int countPopulation(char target[][NUM_COLS]) {
	int population = 0;
	for (int i = 0; i < NUM_ROWS; i++) {
		for (int j = 0; j < NUM_COLS; j++) {
			if (target[i][j] == ALIVE) {
				population++;
			}
		}
	}
	return population;
}

//I mean... I had to name the function this.
//anyway, depends on basically all the other functions.
//prints out the generation and the grid, prompts the user to continue or quit
//optionIters determines the mode the game will run (see below)
//0:  Manual advance (e.g. press enter to advance generation)
//1:  game will prompt user for number of iterations and then automatically advance for
//		that number of iterations, or until no living cells remain
//-1:  Infinite iterations; game will advance forever (or until no living cells remain)
void getALifeDude(char target[][NUM_COLS], int optionIters) {
	//prints out initial generation and instructs user what to do to continue
	int genCount = 0;
	printf("\n\nGeneration:     0 (Initial configuration from input file)\n");
	printf("Population:     %d\n\n", countPopulation(target));
	printLifeGrid(target);
	char userInput = '\0';
	printf("\n\nPress enter to continue.");
	scanf("%c", &userInput);
	scanf("%c", &userInput);
	system("cls");

	//decides how the program will run based on numIters

	//manual advance mode
	if (optionIters == 0) {
		while (userInput != 'q') {
			genCount++;
			updateOneIteration(target);
			printf("Generation:     %d\n", genCount);
			printf("Population:     %d\n\n", countPopulation(target));
			printLifeGrid(target);
			//system call to sleep for the number of milliseconds indicated
			//Sleep(125);
			if (countPopulation(target) == 0) {
				printf("\n\nWarning: no living cells remain.\n\n");
			}
			printf("\n\nPress enter to continue or q to quit.\n\n");
			scanf("%c", &userInput);
			//"system" -> "clear screen"
			system("cls");
			//"system" -> "press any key to continue prompt"
			//system("pause");
		}
	}
	//infinite iterations mode
	else if (optionIters == -1) {
		int sex = 69;
		int fun = 69;
		while (sex == fun && countPopulation(target) != 0) {
			
			system("cls");
			genCount++;
			updateOneIteration(target);
			printf("Generation:     %d\n", genCount);
			printf("Population:     %d\n\n", countPopulation(target));
			printLifeGrid(target);
			Sleep(125);
			if (countPopulation(target) == 0) {
				printf("\n\nNo living cells remain, stopping.\n\n");
			}
			
		}
	}
	//fixed iterations mode
	else {
		printf("Enter the number of iterations to advance:  ");
		int numIters = 0;
		scanf("%d", &numIters);
		for (int i = 0; i < numIters; i++) {
			system("cls");
			genCount++;
			updateOneIteration(target);
			printf("Generation:     %d\n", genCount);
			printf("Population:     %d\n\n", countPopulation(target));
			printLifeGrid(target);
			Sleep(125);
			if (countPopulation(target) == 0) {
				printf("\n\nNo living cells remain, stopping.\n\n");
			}
		}
	}

	printf("\nStopping.\n\n");
	//eats a newline/return to avoid a minor bug.
	scanf("%c", &userInput);
}

//prints the menu that should be shown whenever looping back to the list of options
void printMenu(void) {
	printf("*** Select an option from the menu below:\n\n");
	printf("1.  Rules for Game of Life\n");
	printf("2.  About Prissy Kitty Productions\n");
	printf("3.  Mode selection descriptions\n");
	printf("4.  Run Game of Life (manual advance)\n");
	printf("5.  Run Game of Life (fixed number of iterations)\n");
	printf("6.  Run Game of Life (run forever)\n");
	printf("7.  Quit\n\n");
}

//prints rules when user selects that option from the menu
void printRules(void) {
	printf("\nGAME OF LIFE INTRO AND RULES\n");
	printf("\nThe Game of Life is a cellular automaton invented by\n");
	printf("John Conway (1937 - 2020) in 1970.  It is a zero player\n");
	printf("game, meaning that once the initial input has been determined,\n");
	printf("the game will \"run\" itself based on a set of specific rules.\n");
	printf("Every element on the grid is referred to as a cell, and a cell's\n");
	printf("behavior is determined by the configuration of the eight surrounding\n");
	printf("cells in its Moore neighborhood.\n\n");
	printf("The rules governing behavior for the next generation are as follows:\n\n");
	printf("*A live cell with fewer than two live neighbors dies.\n");
	printf("*A live cell with greater than three live neighbors dies.\n");
	printf("*A live cell with two or three live neighbors will survive.\n");
	printf("*A dead cell with exactly three live neighbors will become alive.\n\n");
	printf("For more information... just google this shit, you lazy bastard.\n\n");
	printf("Press enter to return.\n\n");

	char tempCharr = '\0';
	scanf("%c", &tempCharr);
	scanf("%c", &tempCharr);
}

//prints an about page when user selects that option from the menu
void printAbout(void) {
	printf("\nABOUT PRISSY KITTY PRODUCTIONS\n");
	printf("\nPrissy Kitty Productions (or PKP, if you prefer, but only if you don't\n");
	printf("value your life) is a subsidiary of the shadowy and nefarious\n");
	printf("Great Lynx Consortium.  Frankly, even by reading this about section\n");
	printf("you are putting your life at risk.  So... yeah...\n\n");
	printf("Use this program at your own risk.\n");
	printf("The developer of this program does not accept any liability for any losses\n");
	printf("or damages from the use of this program, including, but not limited to:\n\n");
	printf("*Fire\n");
	printf("*Loss of life and/or limb\n");
	printf("*Having jackals consume the aformentioned life or limb\n");
	printf("*Acts of God (or Gods, if polytheistic)\n");
	printf("*Nuclear armageddon\n");
	printf("*Dizziness\n");
	printf("*Manufacture of actual sentient life\n\n");
	printf("If you experience an erection lasting longer than three hours while\n");
	printf("using this program, stop IMMEDIATELY, call your doctor, and brag.\n\n");
	printf("Press enter to return.\n\n");

	char tempCharr = '\0';
	scanf("%c", &tempCharr);
	scanf("%c", &tempCharr);
}

//prints the mode selection descriptions page when user selects that option
void printOptions(void) {
	printf("\nMODE SELECTION DESCRIPTIONS\n\n");
	printf("Manual advance: the game will advance one iteration every time\n");
	printf("Enter is pressed on the keyboard.\n\n");
	printf("Fixed numer of iterations: the game will advance automatically the\n");
	printf("number of iterations selected by the user, or until\n");
	printf("there are no living cells remaining.\n\n");
	printf("Run forever: the game will attempt to run forever until\n");
	printf("there are no living cells remaining, your power goes out,\n");
	printf("or you get bored and decide to watch some porn instead.\n\n");
	printf("Note that in all options, the program will first staticly display\n");
	printf("the initial input configuration, and manual advance will be required\n");
	printf("in all modes.\n\n");
	printf("If you still have questions about these options... tough.\n");
	printf("I don't really have any more text here, so... good luck.\n\n");
	printf("Press enter to return.\n\n");

	char tempCharr = '\0';
	scanf("%c", &tempCharr);
	scanf("%c", &tempCharr);
}