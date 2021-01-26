//header for sudoku solver

#define _CRT_SECURE_NO_WARNINGS
#define GRID_LEN 9
#define BOARD_SIZE 81

#include <stdio.h>
#include <Windows.h>

//prints board to console
void displayBoard(int target[][GRID_LEN]);

//initializes logic board
void initializeLogicBoard(int target[BOARD_SIZE][GRID_LEN + 1]);

//prints logic board for debug purposes
void printLogicBoard(int target[BOARD_SIZE][GRID_LEN + 1]);

//counts number of zeroes, i.e. unsolved squares remaining on board
int countUnknownsRemaining(int target[][GRID_LEN]);

//checks the row entries for the current cell to eliminate possibilities
void checkRow(int row, int col, int board[GRID_LEN][GRID_LEN],
		int logicBoard[BOARD_SIZE][GRID_LEN + 1]);

//checks the col entries for the current cell to eliminate possibilities
void checkCol(int row, int col, int board[GRID_LEN][GRID_LEN],
	int logicBoard[BOARD_SIZE][GRID_LEN + 1]);

//checks the 3x3 sector for the current cell to eliminate possibilities
void checkSector(int row, int col, int board[GRID_LEN][GRID_LEN],
	int logicBoard[BOARD_SIZE][GRID_LEN + 1]);

//wrapper to process a cell on the board
//returns 1 if filled in a value in that cell, 0 else
int processCell(int row, int col, int board[GRID_LEN][GRID_LEN],
	int logicBoard[BOARD_SIZE][GRID_LEN + 1]);

//wrapper to ... y'know
void commitSudoku(int board[GRID_LEN][GRID_LEN]);