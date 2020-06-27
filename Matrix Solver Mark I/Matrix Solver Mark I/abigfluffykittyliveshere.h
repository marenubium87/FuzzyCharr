//header file for Matrix Solver project

#define _CRT_SECURE_NO_WARNINGS
#define NUM_OF_ROWS 3

#include <stdio.h>

//end of program wrapper
void EoPWrapper(void);

//does what it sounds like... prints out the target double two-dimensional array
//to the console.
//required for: a lot of shit.
//pretty print limitations:  (+)abc.xy / -hi.jkl
void printArrayConsole(double target[][NUM_OF_ROWS + 1]);

//prints out the target double two-dimensional array to outfile
//required for: a lot of shit.
//pretty print limitations:  (+)abc.xy / -hi.jkl
void printArray(FILE * outfile, double target[][NUM_OF_ROWS + 1]);

//reads int values from infile and populates target double two-dimensional array
//of size (NUM_OF_ROWS) x (NUM OF ROWS + 1)
//also prints out the array to the console.
//preconditions:  must read (NUM_OF_ROWS)*(NUM_OF_ROWS + 1) values
//fills row first, before column
//requires: printArrayConsole
void populateArray(FILE * infile, double target[][NUM_OF_ROWS + 1]);

//checks target array for linear dependence
//returns 1 if target array is linearly independent
//returns 0 if target array is linearly dependent
//returns -1 if target array is a system with no solution
//required for: commitRREF
int checkLinearIndependence(FILE * outfile, double target[][NUM_OF_ROWS + 1]);

//normalizes the row with index rowIndex in target array
//that is to say, makes it so that the value of the target[i][i] element is divided by itself to equal 1
//and all other elements of the row are divided by the same number
//also writes the current operation to outfile.
//returns 1 if no problems arose, 0 otherwise
//required for: commitRREF
int normalizeRow(FILE * outfile, double target[][NUM_OF_ROWS + 1], int rowIndex);

//performs a single row operation using opRow on adjRow to zero out target column of adjRow
//opRow = operation Row, e.g. the Row used to perform operations
//adjRow = adjusted Row, e.g. the Row that operations are performed on
//also writes the current operation to outfile.
//returns 1 if no problems arose, 0 otherwise
//required for: commitRREF
int performRowOps(FILE * outfile, double target[][NUM_OF_ROWS + 1], int opRow, int adjRow, int targetColumn);

//puts it all together now.  wrapper function to conduct row operations on target array
//and put it into row-reduced echelon form
//writes the operations and the intermediate matrices after each operation to outfile.
//depends on checkLinearIndependence, normalizeRow, performRowOps, and printArrayConsole
void commitRREF(FILE * outfile, double target[][NUM_OF_ROWS + 1]);