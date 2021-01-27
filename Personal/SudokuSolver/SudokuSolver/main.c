//sudoku solver
//26 jan 2021

#include "SudokuSolver.h"

int main() {
	int board[GRID_LEN][GRID_LEN] = {
		{1,0,0,4,8,9,0,0,6},
		{7,3,0,0,0,0,0,4,0},
		{0,0,0,0,0,1,2,9,5},
		{0,0,7,1,2,0,6,0,0},
		{5,0,0,7,0,3,0,0,8},
		{0,0,6,0,9,5,7,0,0},
		{9,1,4,6,0,0,0,0,0},
		{0,2,0,0,0,0,0,3,7},
		{8,0,0,5,1,2,0,0,4}
	};

	printf("Initial board state:\n\n");
	displayBoard(board);

	//YASSSSSSSSS
	commitSudoku(board);

	system("pause");
	return 0;
}