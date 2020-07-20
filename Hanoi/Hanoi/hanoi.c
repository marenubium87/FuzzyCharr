#include "hanoi.h"

void moveCurrentDisk(int diskArray[], int currentDisk) {
	if (diskArray[currentDisk] < 3) {
		printf("Move disk %2d from peg %d ",
			currentDisk, diskArray[currentDisk]);
		diskArray[currentDisk]++;
		printf("to peg %d.\n", diskArray[currentDisk]);
	}
	else if (diskArray[currentDisk] == 3) {
		printf("Move disk %2d from peg %d ",
			currentDisk, diskArray[currentDisk]);
		diskArray[currentDisk]++;
		printf("to peg 2.\n");
	}
	else if (diskArray[currentDisk] == 4) {
		printf("Move disk %2d from peg 2 ",
			currentDisk);
		diskArray[currentDisk] = 1;
		printf("to peg %d.\n", diskArray[currentDisk]);
	}
}

void hanoi(int diskArray[], int currentDisk) {
	if (currentDisk == 1) {
		if (diskArray[currentDisk] == 1) {
			printf("Move disk %2d from peg %d ", 
				currentDisk, diskArray[currentDisk]);
			diskArray[currentDisk] = 3;
			printf("to peg %d.\n", diskArray[currentDisk]);
		}
		else if (diskArray[currentDisk] == 3) {
			printf("Move disk %2d from peg %d ",
				currentDisk, diskArray[currentDisk]);
			diskArray[currentDisk] = 1;
			printf("to peg %d.\n", diskArray[currentDisk]);
		}
	}
	else {
		
		hanoi(diskArray, currentDisk - 1);
		moveCurrentDisk(diskArray, currentDisk);
		hanoi(diskArray, currentDisk - 1);
		moveCurrentDisk(diskArray, currentDisk);
		hanoi(diskArray, currentDisk - 1);
	}
}