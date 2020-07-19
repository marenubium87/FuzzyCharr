//source file for Maze project

#include "maze.h"

//prints out maze to the console
void printMaze(char maze[MAZE_ROWS][MAZE_COLS]) {
	for (int i = 0; i < MAZE_ROWS; i++) {
		for (int j = 0; j < MAZE_COLS; j++) {
			printf("%c ", maze[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
}

//aux function for traverseMaze
//returns 1 if attemptDir direction is valid based on prevDir direction
//given the currRow and currCol... returns 0 if invalid
//and returns -1 if code fucked up... hopefully never.
//NOTE! prevDir is cardinal: e.g. n, e, s, w
//		however, currDir is RELATIVE: forward, left, right, back
int isValidPath(char maze[MAZE_ROWS][MAZE_COLS],
	char prevDir, int currRow, int currCol, char attemptDir) {

	switch (prevDir) {
		case 'n':
			if (attemptDir == 'f') {
				//if previous direction was north, then forward is also north
				//so check the spot which decrements the row by 1
				//to make sure it's in bounds and empty
				if (maze[currRow - 1][currCol] == EMPTY &&
					currRow - 1 >= 0) {
					return 1;
				}
				else {
					return 0;
				}
			}
			if (attemptDir == 'r') {
				//if previous direction was north, then right is east
				//so check the spot which increments the col by 1
				//to make sure it's in bounds and empty
				if (maze[currRow][currCol + 1] == EMPTY &&
					currCol + 1 < MAZE_COLS) {
					return 1;
				}
				else {
					return 0;
				}
			}
			if (attemptDir == 'l') {
				//if previous direction was north, then left is west
				//so check the spot which decrements the col by 1
				//to make sure it's in bounds and empty
				if (maze[currRow][currCol - 1] == EMPTY &&
					currCol - 1 >= 0) {
					return 1;
				}
				else {
					return 0;
				}
			}
			if (attemptDir == 'b') {
				//moving backwards should always be fine
				//b/c that's where you came from
				return 1;
			}
			break;
		case 'e':
			//analogous to the comments for the first case
			//except for the attempted directions need to be updated
			//for previous direction east
			if (attemptDir == 'l') {
				if (maze[currRow - 1][currCol] == EMPTY &&
					currRow - 1 >= 0) {
					return 1;
				}
				else {
					return 0;
				}
			}
			if (attemptDir == 'f') {
				if (maze[currRow][currCol + 1] == EMPTY &&
					currCol + 1 < MAZE_COLS) {
					return 1;
				}
				else {
					return 0;
				}
			}
			if (attemptDir == 'b') {
				//moving backwards should always be fine
				//b/c that's where you came from
				return 1;
			}
			if (attemptDir == 'r') {
				if (maze[currRow + 1][currCol] == EMPTY &&
					currRow + 1 < MAZE_ROWS) {
					return 1;
				}
				else {
					return 0;
				}
			}
			break;
		case 'w':
			//analogous to the comments for the first case
			//except for the attempted directions need to be updated
			//for previous direction west
			if (attemptDir == 'r') {
				if (maze[currRow - 1][currCol] == EMPTY &&
					currRow - 1 >= 0) {
					return 1;
				}
				else {
					return 0;
				}
			}
			if (attemptDir == 'b') {
				//moving backwards should always be fine
				//b/c that's where you came from
				return 1;
			}
			if (attemptDir == 'f') {
				if (maze[currRow][currCol - 1] == EMPTY &&
					currCol - 1 >= 0) {
					return 1;
				}
				else {
					return 0;
				}
			}
			if (attemptDir == 'l') {
				if (maze[currRow + 1][currCol] == EMPTY &&
					currRow + 1 < MAZE_ROWS) {
					return 1;
				}
				else {
					return 0;
				}
			}
			break;
		case 's':
			//analogous to the comments for the first case
			//except for the attempted directions need to be updated
			//for previous direction south
			if (attemptDir == 'b') {
				//moving backwards should always be fine
				//b/c that's where you came from
				return 1;
			}
			if (attemptDir == 'l') {
				if (maze[currRow][currCol + 1] == EMPTY &&
					currCol + 1 < MAZE_COLS) {
					return 1;
				}
				else {
					return 0;
				}
			}
			if (attemptDir == 'r') {
				if (maze[currRow][currCol - 1] == EMPTY &&
					currCol - 1 >= 0) {
					return 1;
				}
				else {
					return 0;
				}
			}
			if (attemptDir == 'f') {
				if (maze[currRow + 1][currCol] == EMPTY &&
					currRow + 1 < MAZE_ROWS) {
					return 1;
				}
				else {
					return 0;
				}
			}
			break;
		default:
			printf("Yeah, something got fucked up... check your code.\n");
			return -1;
			break;
	}
}

//aux function for traverseMaze
//uses previous row, col and current row, col to determine which direction
//we've traveled in since the previous turn.
char getPreviousDir(int prevRow, int prevCol, 
	int currRow, int currCol) {
	//if there is no offset between the previous row and the current one
	//means we either went east or west
	if (prevRow == currRow) {
		if (currCol > prevCol) {
			return 'e';
		}
		else {
			return 'w';
		}
	}
	else {
		if (currRow > prevRow) {
			return 's';
		}
		else {
			return 'n';
		}
	}
}

//aux function for traverseMaze
//moves in the relative (forward, left, right, back) nextDir indicated
//based on prevDir cardinal direction (NESW) and the current location
//by updating *currRow and *currCol
void moveNext(char prevDir, int * prevRow, int * prevCol,
	int * currRow, int * currCol, char nextDir) {

	//first set our current position to the previous position
	//or we're going to lose it.
	*prevRow = *currRow;
	*prevCol = *currCol;

	switch (prevDir) {
	case 'n':
		switch (nextDir) {
			//if we were going north and then we go forward again,
			//that is the same as decrementing the row, etc.
		case 'f':
			printf("Moving north ");
			(*currRow)--;
			break;
		case 'l':
			printf("Moving  west ");
			(*currCol)--;
			break;
		case 'r':
			printf("Moving  east ");
			(*currCol)++;
			break;
		case 'b':
			printf("Moving south ");
			(*currRow)++;
			break;
		default:
			printf("Something fucked up.  Check code.\n\n");
			break;
		}
		break;
	case 'e':
		switch (nextDir) {
			//if we were going east and then we go forward again,
			//that is the same as incrementing the col, etc.
		case 'l':
			printf("Moving north ");
			(*currRow)--;
			break;
		case 'b':
			printf("Moving  west ");
			(*currCol)--;
			break;
		case 'f':
			printf("Moving  east ");
			(*currCol)++;
			break;
		case 'r':
			printf("Moving south ");
			(*currRow)++;
			break;
		default:
			printf("Something fucked up.  Check code.\n\n");
			break;
		}
		break;
	case 'w':
		switch (nextDir) {
			//if we were going west and then we go forward again,
			//that is the same as decrementing the col, etc.
		case 'r':
			printf("Moving north ");
			(*currRow)--;
			break;
		case 'f':
			printf("Moving  west ");
			(*currCol)--;
			break;
		case 'b':
			printf("Moving  east ");
			(*currCol)++;
			break;
		case 'l':
			printf("Moving south ");
			(*currRow)++;
			break;
		default:
			printf("Something fucked up.  Check code.\n\n");
			break;
		}
		break;
	case 's':
		switch (nextDir) {
			//if we were going south and then we go forward again,
			//that is the same as incrementing the row, etc.
		case 'b':
			printf("Moving north ");
			(*currRow)--;
			break;
		case 'r':
			printf("Moving  west ");
			(*currCol)--;
			break;
		case 'l':
			printf("Moving  east ");
			(*currCol)++;
			break;
		case 'f':
			printf("Moving south ");
			(*currRow)++;
			break;
		default:
			printf("1Something fucked up.  Check code.\n\n");
			break;
		}
		break;
	default:
		printf("2Something fucked up.  Check your fucking code.\n\n");
		break;
	}
	printf("from r%d c%d to r%d c%d.\n", 
		*prevRow, *prevCol, *currRow, *currCol);
}


//time to traverse the maze.
//algorithm is simple - for each step, try directions in this order
//and take the first one that works:  right, forward, left, back
void traverseMaze(char maze[MAZE_ROWS][MAZE_COLS], int * failCounter,
	int * prevRow, int * prevCol, int * currRow, int * currCol) {
	
	//the fail counter increments every time we hit the top left of the maze
	if (*currRow == 0 && *currCol == 0) {
		(*failCounter)++;
	}
	
	//base case is reaching the end or failing too many times
	//if we fail three times that means we're hosed, since there are
	//only two directions out of the top left at max.
	if (*failCounter >= 3) {
		printf("Onoes, can't find solution.\n\n");
		return;
	}
	else if ((*currRow == MAZE_ROWS - 1 && *currCol == MAZE_COLS - 1)) {
		printf("\nAnd we're done!\n\n");
		return;
	}
	else {
		//otherwise, do traversal things

		//determine which direction we just came from
		char prevDir = getPreviousDir(*prevRow, *prevCol, *currRow, *currCol);

		//based on that, try current directions 
		//in following order: right, forward, left, back
		//take the first one that works, then traverse again
		if (isValidPath(maze, prevDir, *currRow, *currCol, 'r')) {
			moveNext(prevDir, prevRow, prevCol, currRow, currCol, 'r');
		}
		else if (isValidPath(maze, prevDir, *currRow, *currCol, 'f')) {
			moveNext(prevDir, prevRow, prevCol, currRow, currCol, 'f');
		}
		else if (isValidPath(maze, prevDir, *currRow, *currCol, 'l')) {
			moveNext(prevDir, prevRow, prevCol, currRow, currCol, 'l');
		}
		else if (isValidPath(maze, prevDir, *currRow, *currCol, 'b')) {
			moveNext(prevDir, prevRow, prevCol, currRow, currCol, 'b');
		}
	}

	//now that current position is updated, we go again.
	traverseMaze(maze, failCounter, prevRow, prevCol, currRow, currCol);
	return;
}