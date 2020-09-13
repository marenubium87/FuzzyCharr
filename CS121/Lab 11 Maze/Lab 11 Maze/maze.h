//header for Maze project

#define _CRT_SECURE_NO_WARNINGS
#define MAZE_ROWS 8
#define MAZE_COLS 10
#define EMPTY '.'
#define WALL '*'


#include <stdio.h>
#include <Windows.h>

//prints out maze to the console
void printMaze(char maze[MAZE_ROWS][MAZE_COLS]);

//aux function for traverseMaze
//returns 1 if attemptDir direction is valid based on prevDir direction
//given the currRow and currCol... returns 0 if invalid
//and returns -1 if code fucked up... hopefully never.
//NOTE! prevDir is cardinal: e.g. n, e, s, w
//		however, currDir is RELATIVE: forward, left, right, back
int isValidPath(char maze[MAZE_ROWS][MAZE_COLS],
	char prevDir, int currRow, int currCol, char attemptDir);

//aux function for traverseMaze
//uses previous row, col and current row, col to determine which direction
//we've traveled in since the previous turn.
char getPreviousDir(int prevRow, int prevCol,
	int currRow, int currCol);

//time to traverse the maze.
//algorithm is simple - for each step, try directions in this order
//and take the first one that works:  right, forward, left, back
void traverseMaze(char maze[MAZE_ROWS][MAZE_COLS], int * failCounter,
	int * prevRow, int * prevCol, int * currRow, int * currCol);