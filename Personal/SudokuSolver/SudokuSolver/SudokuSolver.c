//source for sudoku solver

#include "SudokuSolver.h"

//displays board to console
void displayBoard(int target[][GRID_LEN]) {
	for (int i = 0; i < GRID_LEN; i++) {
		if (i % 3 == 0) {
			printf("--------------------------\n");
		}
		for (int j = 0; j < GRID_LEN; j++) {
			if (j % 3 == 0) {
				printf("| ");
			}
			printf("%d ", target[i][j]);
		}
		printf(" |");
		printf("\n");
	}
	printf("--------------------------\n");
}

//initializes logic board to 81 rows of:
// 9 1 1 1 1 1 1 1 1 1
// ^ (               ) <- specific possibilities remaining 1-9
// ^
// num possible values remaining for cell; = sum of 1s in row
void initializeLogicBoard(int target[BOARD_SIZE][GRID_LEN + 1]) {
	for (int i = 0; i < BOARD_SIZE; i++) {
		target[i][0] = 9;
		for (int j = 1; j < GRID_LEN + 1; j++) {
			target[i][j] = 1;
		}
	}
}

//prints logic board for debug purposes
void printLogicBoard(int target[BOARD_SIZE][GRID_LEN + 1]) {
	printf("Logic Board:\n");
	for (int i = 0; i < BOARD_SIZE; i++) {
		printf("Cell %2d:  ", i);
		for (int j = 0; j < GRID_LEN + 1; j++) {
			printf("%d ", target[i][j]);
		}
		printf("\n");
	}
}

//counts number of zeroes, i.e. unsolved squares remaining on board
int countUnknownsRemaining(int target[][GRID_LEN]) {
	int numUnknownsRemaining = 0;
	for (int i = 0; i < GRID_LEN; i++) {
		for (int j = 0; j < GRID_LEN; j++) {
			if (target[i][j] == 0) {
				numUnknownsRemaining++;
			}
		}
	}
	return numUnknownsRemaining;
}

//checks the row entries for the current cell to eliminate possibilities
void checkRow(int row, int col, int board[GRID_LEN][GRID_LEN],
		int logicBoard[BOARD_SIZE][GRID_LEN + 1]) {
	//determine which cell we are in
	int cellID = GRID_LEN * row + col;

	//increment across columns, skip the cell in question
	for (int j = 0; j < GRID_LEN; j++) {
		if (j != col && board[row][j] > 0 &&
				logicBoard[cellID][board[row][j]] == 1) {
			logicBoard[cellID][board[row][j]]--;
			logicBoard[cellID][0]--;
		}
	}
}

//checks the col entries for the current cell to eliminate possibilities
void checkCol(int row, int col, int board[GRID_LEN][GRID_LEN],
		int logicBoard[BOARD_SIZE][GRID_LEN + 1]) {
	//determine which cell we are in
	int cellID = GRID_LEN * row + col;

	//increment down rows, skip the cell in question
	for (int i = 0; i < GRID_LEN; i++) {
		if (i != row && board[i][col] > 0 &&
				logicBoard[cellID][board[i][col]] == 1) {
			logicBoard[cellID][board[i][col]]--;
			logicBoard[cellID][0]--;
		}
	}
}

//checks the 3x3 sector for the current cell to eliminate possibilities
void checkSector(int row, int col, int board[GRID_LEN][GRID_LEN],
		int logicBoard[BOARD_SIZE][GRID_LEN + 1]) {
	//determine which cell we are in
	int cellID = GRID_LEN * row + col;

	//how many rols and cols do we have to offset to be in the sector
	//we are currently in?
	int rowOffset = row / 3 * 3;
	int colOffset = col / 3 * 3;

	//check this 3x3 sector now, skip the cell that we're evaluatihng for
	for (int i = rowOffset; i < rowOffset + 3; i++) {
		for (int j = colOffset; j < colOffset + 3; j++) {
			if (!(i == row && j == col) && board[i][j] > 0 &&
				logicBoard[cellID][board[i][j]] == 1) {
				logicBoard[cellID][board[i][j]]--;
				logicBoard[cellID][0]--;
			}
		}
	}
}

//wrapper to process a cell on the board
//returns 1 if filled in a value in that cell, 0 else
int processCell(int row, int col, int board[GRID_LEN][GRID_LEN],
		int logicBoard[BOARD_SIZE][GRID_LEN + 1])
{
	//determine which cell we are in
	int cellID = GRID_LEN * row + col;

	checkRow(row, col, board, logicBoard);
	checkCol(row, col, board, logicBoard);
	checkSector(row, col, board, logicBoard);

	//have we eliminated all possibilities for that cell?
	//if so, fill in the correct value
	if (logicBoard[cellID][0] == 1) {
		int i = 1;
		for (; i < GRID_LEN + 1; i++) {
			if (logicBoard[cellID][i] == 1) {
				logicBoard[cellID][i]--;
				board[row][col] = i;
				logicBoard[cellID][0]--;
				break;
			}
		}
		//printf("Entered value of %d into row %d col %d.\n",
		//	i, row + 1, col + 1);

		return 1;
	}
	return 0;
}

//wrapper to ... y'know
void commitSudoku(int board[GRID_LEN][GRID_LEN]) {
	int logicBoard[BOARD_SIZE][GRID_LEN + 1];
	initializeLogicBoard(logicBoard);
	int numUnknowns = countUnknownsRemaining(board);

	int changedFlag = 0;
	while (numUnknowns > 0) {
		for (int i = 0; i < GRID_LEN; i++) {
			for (int j = 0; j < GRID_LEN; j++) {
				if (board[i][j] == 0) {
					//system("cls");
					changedFlag = processCell(i, j, board, logicBoard);
					if (changedFlag == 1) {
						//displayBoard(board);
						numUnknowns--;
						//system("pause");
					}
				}
			}
		}
	}
	printf("\nSolved board state:\n");
	displayBoard(board);
}