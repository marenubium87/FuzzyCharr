//header file for Game of Life project

#define _CRT_SECURE_NO_WARNINGS

//dimensions of the "game board" for this project.
#define NUM_ROWS 28
#define NUM_COLS 28

//x and y coordinates on the grid for where grid will be displayed
//x_min and y_min are the furthest left and top index of the view, respectively
//x_len and y_len are the horizontal and vertical length of the view, respectively
#define VIEW_ROW_OFFSET 0
#define VIEW_COL_OFFSET 0
//grids larger than about 36 are not recommended.
#define VIEW_NUM_ROWS 28
#define VIEW_NUM_COLS 28

//symbols for the four relevant states in cell automata
#define BIRTH '+'
#define ALIVE 'O'
#define DYING '-'
#define EMPTY '.'

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

//end of program cleanup
void EoPCleanup(void);

//prints out 2D array to the console with window location and size
//determined by the constants in the header file
//NOTE: remember that the number of rows is actually related to HEIGHT constants
//		similarly, the number of columns is actually related to WIDTH constants
void printLifeGrid(char target[][NUM_COLS]);

//populates the life array with coordinates (number pairs)
//in the format R C (row, then column... not x,y!) from infile
void populateLifeGrid(FILE * infile, char target[][NUM_COLS]);

//returns the number of live cells in the Moore neighborhood (check wikipedia if you don't know)
//of the element at (rowIndex, colIndex), excluding the element itself.
int countAdjLiveCells(char target[][NUM_COLS], int rowIndex, int colIndex);

//updates the entire grid for one "half" iteration using the rules for game of life
//meaning that cells that are born are temporarily assigned the BIRTH symbol (see consts)
//and cells that are dying are temporarily assigned the DYING symbol (see consts)
void updateOneHalfIteration(char target[][NUM_COLS]);

//updates the entire grid for a full iteration using the rules for game of life
//essentially doing the half iteration, then going through the grid again and
//assigning BIRTH symbols to ALIVE; DYING symbols to EMPTY
//dependencies: updateOneHalfIteration, for some unknown reason /s
void updateOneIteration(char target[][NUM_COLS]);

//counts the number of cells that are alive at any given point.
//will only count cells marked with ALIVE symbol; will not count birthing or dying cells.
int countPopulation(char target[][NUM_COLS]);

//I mean... I had to name the function this.
//anyway, depends on basically all the other functions.
//prints out the generation and the grid, prompts the user to continue or quit
//optionIters determines the mode the game will run (see below)
//0:  Manual advance (e.g. press enter to advance generation)
//1:  game will prompt user for number of iterations and then automatically advance for
//		that number of iterations, or until no living cells remain
//-1:  Infinite iterations; game will advance forever (or until no living cells remain)
void getALifeDude(char target[][NUM_COLS], int numIters);

//prints the menu that should be shown whenever looping back to the list of options
void printMenu(void);

//prints rules when user selects that option from the menu
void printRules(void);

//prints an about page when user selects that option from the menu
void printAbout(void);

//prints the mode selection descriptions page when user selects that option
void printOptions(void);