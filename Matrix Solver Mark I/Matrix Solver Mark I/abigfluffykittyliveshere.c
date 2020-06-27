//source file for Matrix Project

#include "abigfluffykittyliveshere.h"

//end of program wrapper
void EoPWrapper(void) {
	printf("\nEnd of program, press Enter to continue.\n");
	char tempCharr = '\0';
	scanf("%c", &tempCharr);
	scanf("%c", &tempCharr);
}

//does what it sounds like... prints out the target double two-dimensional array
//to the console.
//required for: a lot of shit.
//pretty print limitations:  (+)abc.xy / -hi.jkl
void printArrayConsole(double target[][NUM_OF_ROWS + 1]) {
	
	printf("Current array composition:\n\n");

	for (int i = 0; i < NUM_OF_ROWS; i++) {
		printf("|  ");
		for (int j = 0; j < NUM_OF_ROWS + 1; j++) {
			printf("%7.3lf  ", target[i][j]);
		}
		printf("|\n\n");
	}
}

//prints out the target double two-dimensional array to outfile
//required for: a lot of shit.
//pretty print limitations:  (+)abc.xy / -hi.jkl
void printArray(FILE * outfile, double target[][NUM_OF_ROWS + 1]) {
	fprintf(outfile, "Current array composition:\n\n");
	for (int i = 0; i < NUM_OF_ROWS; i++) {
		fprintf(outfile, "|  ");
		for (int j = 0; j < NUM_OF_ROWS + 1; j++) {
			fprintf(outfile, "%7.3lf  ", target[i][j]);
		}
		fprintf(outfile, "|\n");
	}
	fprintf(outfile, "\n\n");
}

//reads int values from infile and populates target double two-dimensional array
//of size (NUM_OF_ROWS) x (NUM OF ROWS + 1)
//also prints out the array to the console.
//preconditions:  must read (NUM_OF_ROWS)*(NUM_OF_ROWS + 1) values
//fills row first, before column
//requires: printArrayConsole
void populateArray(FILE * infile, double target[][NUM_OF_ROWS + 1]) {
	printf("  Populating array from infile...  ");
	int nextInt = 0;
	for (int i = 0; i < NUM_OF_ROWS; i++) {
		for (int j = 0; j < NUM_OF_ROWS + 1; j++) {
			fscanf(infile, "%d", &nextInt);
			target[i][j] = nextInt;
		}
	}
	printf("done.\n");
	printf("  Array read from infile:\n\n");
	printArrayConsole(target);
}

//checks target array for linear dependence
//returns 1 if target array is linearly independent
//returns 0 if target array is linearly dependent
//returns -1 if target array is a system with no solution
//informs user on the console if array is not linearly independent
//required for: commitRREF
int checkLinearIndependence(FILE * outfile, double target[][NUM_OF_ROWS + 1]) {
	//checks through all rows
	for (int i = 0; i < NUM_OF_ROWS; i++) {
		int liFlag = 0;
		//for each row, check all of the nonaugmented elements
		for (int j = 0; j < NUM_OF_ROWS; j++) {
			//if any entries in row aren't zero, row is consistent with linear independence
			//that row no longer needs to be checked
			if (target[i][j] != 0) {
				liFlag = 1;
				break;
			}
		}
		//if the for loop completes and liFlag is still 0, that means we found
		//a row whose nonaugmented elements are all zero.
		//in that case we need to determine whether the augmented element is zero or not.
		//note that we're checking the very last column, and since columns = rows + 1,
		//the index of the very last column is the same numerical value as NUM_OF_ROWS
		if (liFlag == 0) {
			if (target[i][NUM_OF_ROWS] != 0) {
				//this is the no solutions case
				printf("Error: target system has no valid solution.  Aborting.\n\n");
				fprintf(outfile, "Error: target system has no valid solution.  Aborting calculation.\n\n");
				return -1;
			}
			else {
				//otherwise we're in the situation where all the values are zero
				//and we have a linearly dependent array
				printf("Error: target system is not linearly independent.  Aborting.\n\n");
				fprintf(outfile, "Error: target system is not linearly independent.  Aborting calculation.\n\n");
				return 0;
			}
		}
	}
	//if the code executes the entire for loop without already returning a value
	//then array is linearly independent
	return 1;
}

//normalizes the row with index rowIndex in target array
//that is to say, makes it so that the value of the target[i][i] element is divided by itself to equal 1
//and all other elements of the row are divided by the same number
//also writes the current operation to outfile.
//returns 1 if no problems arose, 0 otherwise
//required for: commitRREF
int normalizeRow(FILE * outfile, double target[][NUM_OF_ROWS + 1], int rowIndex) {
	
	double divisor = target[rowIndex][rowIndex];
	if (divisor == 0) {
		printf("Error!  Division by zero in function normalizeRow.  Aborting.\n\n");
		fprintf(outfile, "Error!  Division by zero in function normalizeRow.  Calculations aborted.\n\n");
		return 0;
	}
	//prints the imminent operation to outfile.
	fprintf(outfile, "Divide row %d by %7.3lf:\n\n", rowIndex + 1, divisor);
	for (int i = 0; i < NUM_OF_ROWS + 1; i++) {
		target[rowIndex][i] /= divisor;
	}
	return 1;
}

//performs a single row operation using opRow on adjRow to zero out target column of adjRow
//opRow = operation Row, e.g. the Row used to perform operations
//adjRow = adjusted Row, e.g. the Row that operations are performed on
//also writes the current operation to outfile.
//returns 1 if no problems arose, 0 otherwise
//required for: commitRREF
int performRowOps(FILE * outfile, double target[][NUM_OF_ROWS + 1], int opRow, int adjRow, int targetColumn) {
	//if the opRow has a zero in the targetColumn, something went horribly wrong
	if (target[opRow][targetColumn] == 0) {
		printf("Error!  Division by zero in function performRowOps.  Aborting.\n\n");
		fprintf(outfile, "Error!  Division by zero in function performRowOps.  Calculation aborted.\n\n");
		return 0;
	}
	
	//figures out what opRow needs to be multiplied by to cancel out the value
	//of targetColumn in adjRow
	double multiplier = -target[adjRow][targetColumn] / target[opRow][targetColumn];

	//writes imminent operation to outfile.
	fprintf(outfile, "Multiply row %d by %7.3lf and add to row %d:\n\n", opRow + 1, multiplier, adjRow + 1);
	for (int i = 0; i < NUM_OF_ROWS + 1; i++) {
		target[adjRow][i] += multiplier * target[opRow][i];
	}
	return 1;
}

//puts it all together now.  wrapper function to conduct row operations on target array
//and put it into row-reduced echelon form
//writes the operations and the intermediate matrices after each operation to outfile.
//depends on checkLinearIndependence, normalizeRow, performRowOps, and printArrayConsole
void commitRREF(FILE * outfile, double target[][NUM_OF_ROWS + 1]) {
	printf("  Committing rref algorithm to target array\n  and writing solution to outfile...\n\n");
	int flagLI = 0;

	fprintf(outfile, "Initial array read from infile:\n\n");
	printArray(outfile, target);

	//first pass to check if array is linearly independent... no point doing this if array isn't.
	flagLI = checkLinearIndependence(outfile, target);
	if (flagLI < 1) {
		return;
	}

	//great, if it passes that test, then...
	//flags for normalize row and row ops... these two in addition to flag for linear independence
	//allows the function to be aborted after any anomaly.
	int flagNR = 0, flagRO = 0;
	for (int i = 0; i < NUM_OF_ROWS; i++) {
		//normalize the row, use it to reduce the other rows, then check to see if the system is still
		//linearly independent at this point... if not, stop.

		//first is row normalization.  normalize the current row and print out the intermediate matrix
		//if everything went well.
		flagNR = normalizeRow(outfile, target, i);
		//aborts function if normalizeRow ran into an issue.
		if (flagNR == 0) {
			return;
			}
		printArray(outfile, target);

		//do the row operations for every row that isn't itself and prints out the intermediate matrices.
		for (int j = 0; j < NUM_OF_ROWS; j++) {
			if (i != j) {
				flagRO = performRowOps(outfile, target, i, j, i);
				//aborts function if the last performRowOps ran into an issue.
				if (flagRO == 0) {
					return;
				}
				printArray(outfile, target);
			}
		}

		//then check for linear independence again before repeating the process with the next row.
		flagLI = checkLinearIndependence(outfile, target);
		//aborts function if the array is no longer linearly independent.
		if (flagLI < 1) {
			return;
		}
	}

	//and that's it at this point.  let the user know on the console.
	printf("  rref algorithm complete.  Check outfile for results.\n\n");
	fprintf(outfile, "rref operations complete.  End of output.");
}