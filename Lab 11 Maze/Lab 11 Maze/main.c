/*
* Aerie, CS121
* Instructor: Reynx <3
* Maze Project (Lab 11 Recursion)
* 19 Jul 2020
*/

#include "maze.h"

int main() {
	//containers for previous row and column and failCounter
	int prevRow = -1;
	int prevCol = -1;
	int currRow = 0;
	int currCol = 0;
	int failCounter = 0;

	//first maze starts here
	//set MAZE_ROWS 5, MAZE_COLS 5
	/*char maze1[MAZE_ROWS][MAZE_COLS] = {
		'.', '.', '.', '.', '.',
		'.', '.', '*', '.', '.',
		'.', '.', '*', '.', '.',
		'.', '.', '*', '.', '.',
		'.', '.', '*', '.', '.'
	};*/
	//first maze ends here


	//second maze here
	//set MAZE_ROWS 5, MAZE_COLS 6
	//char maze2[MAZE_ROWS][MAZE_COLS] = {
	//	'.', '.', '*', '.', '.', '.',
	//	'*', '.', '*', '.', '*', '*',
	//	'.', '.', '*', '.', '.', '.',
	//	'.', '*', '*', '.', '*', '.',
	//	'.', '.', '.', '.', '*', '.'
	//};
	//second maze ends here

	//third maze here
	//set MAZE_ROWS 8, MAZE_COLS 10
	char maze3[MAZE_ROWS][MAZE_COLS] = {
		'.', '*', '.', '*', '.', '.', '.', '.', '.', '.',
		'.', '*', '.', '*', '.', '*', '*', '*', '*', '.',
		'.', '.', '.', '*', '.', '.', '.', '*', '.', '.',
		'*', '*', '.', '*', '*', '*', '.', '*', '.', '*',
		'.', '.', '.', '*', '.', '.', '.', '*', '.', '.',
		'.', '*', '*', '*', '.', '*', '*', '*', '*', '.',
		'.', '.', '.', '.', '.', '*', '.', '.', '*', '.',
		'*', '*', '*', '*', '*', '*', '.', '.', '.', '.',
	};
	//third maze ends here
	
	//change arguments for maze to the correct maze number
	printMaze(maze3);
	printf("Starting at r%d, c%d and attempting to traverse maze.\n\n",
		currRow, currCol);
	traverseMaze(maze3, &failCounter, &prevRow, &prevCol, 
		&currRow, &currCol);


	system("pause");
	return 0;
}