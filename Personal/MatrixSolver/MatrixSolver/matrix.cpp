//source for matrix class

#include "matrix.h"

//initializes matrix with number of newRows and newCols from heap
//if no arguments, creates a "null" matrix with no memory allocated
//for the array
Matrix::Matrix(int newRows, int newCols) {
	rows = newRows;
	cols = newCols;

	if (rows == 0) {
		arr = nullptr;
	}
	else {
		arr = new Rational[rows * cols];
		Rational zero(0);
		for (int i = 0; i < rows * cols; i++) {
			arr[i] = zero;
		}
	}
}

//copy constructor
Matrix::Matrix(Matrix const & original) {
	//necessary so that when assignment operator is invoked
	//it doesn't attempt to delete from the garbage data
	//arr is initialized to
	arr = nullptr;
	*this = original;
}

//overloaded assignment operator
Matrix & Matrix::operator=(Matrix const & rhs) {
	//if array was not empty, delete it to prevent memory leaking
	if (arr != nullptr) {
		delete[] arr;
	}
	rows = rhs.getRows();
	cols = rhs.getCols();

	//makes deep copy of matrix as opposed to shallow copy of pointer only
	arr = new Rational[rows * cols];
	for (int i = 0; i < rows * cols; i++) {
		arr[i] = rhs.arr[i];
	}
	return *this;
}

//calls Rational's reduce on every entry of the matrix
void Matrix::reduce() {
	for (int i = 0; i < rows * cols; i++) {
		arr[i].reduce();
	}
}

//overloaded [] operator for 2D matrix operations
Rational * Matrix::operator[](int i) {
	return (arr + i * cols);
}

//multiplies target row by coeff such that its first
//nonzero element is equal to one
void Matrix::normalizeRow(int targetRow) {
	int i = 0;
	//start in target row
	Rational * targetRowStart = arr + targetRow * cols;

	while (targetRowStart[i].getNum() == 0 && i < cols) {
		i++;
	}

	//i is at first entry in row that is not zero
	Rational normalizationCoeff(0);
	Rational one(1);
	if (i < cols) {
		//is that entry already 1?  Don't have to do anything if so.
		if (targetRowStart[i] == one) {
			return;
		}

		//sets normalization coefficient to the value that will 
		//multiply by the first nonzero entry in the row to equal 1
		normalizationCoeff.setNum(targetRowStart[i].getDen(), 0);
		normalizationCoeff.setDen(targetRowStart[i].getNum(), 0);
		normalizationCoeff.setSign(targetRowStart[i].getSign());
		normalizationCoeff.reduce();
	}
	for (; i < cols; i++) {
		targetRowStart[i] = targetRowStart[i] * normalizationCoeff;
	}
}

//swaps row a and row b in matrix
//row index starts with 0, not 1
void Matrix::swapRows(int a, int b) {
	if (!(a < rows && b < rows)) {
		cout << "Error in fcn: swapRows" << endl;
		cout << "Invalid arguments for row swap targets!" << endl;
		cout << "Aborting, no rows swapped." << endl;
		return;
	}

	Rational * startRowA = arr + a * cols;
	Rational * startRowB = arr + b * cols;
	Rational temp(0);
	for (int i = 0; i < cols; i++) {
		temp = startRowA[i];
		startRowA[i] = startRowB[i];
		startRowB[i] = temp;
	}
}

//uses the first nonzero entry in row a to eliminate the entry
//in the corresponding column in row b
void Matrix::rowEliminate(int a, int b) {
	Rational zero(0);
	if (!(a < rows && b < rows)) {
		cout << "Error in fcn: rowEliminate" << endl;
		cout << "Invalid arguments for row elimination targets!" << endl;
		cout << "Aborting, no changes made." << endl;
		return;
	}
	else if (a == b) {
		cout << "Error in fcn: rowEliminate" << endl;
		cout << "Designated row and target row cannot be the same!";
		cout << "Aborting, no changes made." << endl;
		return;
	}
	//finds first nonzero entry in row a
	int i = 0;
	Rational * startRowA = arr + a * cols;
	while (startRowA[i].getNum() == 0 && i < cols) {
		i++;
	}
	if (i >= cols) {
		cout << "Error in fcn: rowEliminate" << endl;
		cout << "Row designated for elimination has no non-zero entries.";
		cout << "Aborting, no changes made." << endl;
		return;
	}

	//if code execution makes it to here, i is at index of first nonzero
	//element of row a, so start row elimination process
	Rational * startRowB = arr + b * cols;
	//if the corresponding value in the target row is already zero,
	//then we don't actually have to do anything
	if (startRowB[i] == zero) {
		return;
	}

	//determine multiplier to make the entry in row b zero
	Rational multiplier = startRowB[i] / startRowA[i];
	for (; i < cols; i++) {
		startRowB[i] = startRowB[i] - multiplier * startRowA[i];
	}
}

//checks to see if target row in the matrix is dependent
//(that is, all zeros)
bool Matrix::isDependentRow(int targetRow) {
	if (targetRow < 0 || targetRow >= rows) {
		cout << "Error in arguments for fcn: isDependentRow" << endl
			<< "Returning FALSE." << endl;
		return false;
	}
	Rational zero(0);
	for (int j = 0; j < cols; j++) {
		if ((*this)[targetRow][j] != zero) {
			return false;
		}
	}
	return true;
}

//checks to see if target row in the matrix is inconsistent
//(that is, all zeroes except last entry, implies no solution to system)
bool Matrix::isInconsistentRow(int targetRow) {
	if (targetRow < 0 || targetRow >= rows) {
		cout << "Error in arguments for fcn: isDependentRow" << endl
			<< "Returning FALSE." << endl;
		return false;
	}
	Rational zero(0);
	int j = 0;
	for (; j < cols - 1; j++) {
		if ((*this)[targetRow][j] != zero) {
			return false;
		}
	}
	//check last col
	if ((*this)[targetRow][j] != zero) {
		return true;
	}
	else {
		return false;
	}
}

//attempts to transform matrix to reduced row echelon form
//using elementary row operations
//NOTE:  For all on-screen output, rows and columns are referenced
//using standard mathematical terminology, that is, the top left cell
//in a matrix is row 1 col 1, not row 0 col 0
void Matrix::rref() {
	cout << "Initial matrix" << endl;
	cout << *this;

	cout << endl << "PERFORMING RREF PROCEDURE..." << endl << endl;
	Rational zero(0);
	//increment through rows
	for (int i = 0; i < rows; i++) {
		//perform a check - is the matrix in an inconsistent (no soln) state?
		//if so, abort, since there's no point to do rref at this point
		for (int j = 0; j < rows; j++) {
			if (isInconsistentRow(j)) {
				cout << "Inconsistent system detected... stopping rref "
					<< "procedure." << endl;
				return;
			}
		}
		
		//flips when row operations are performed at the current pivot
		int rowOpsPerformed = 0;
		//column offset to deal with degenerate matrices
		//start with offset being zero, if entire columns end up being zero
		//offset will kick in
		int offset = 0;
		while (!rowOpsPerformed && i + offset < cols) {
			//is the [i][i + offset] entry zero?
			if ((*this)[i][i + offset] == zero) {
				//do we have a row somewhere below this one to swap it with?
				swapIfAble(i, offset);
			}
			//so either the [i][i + offset] entry is nonzero
			//or a successful swap was performed
			if ((*this)[i][i + offset] != zero) {
				//row normalization
				normalizeRow(i);
				cout << "Normalizing row " << i + 1 << endl;
				cout << *this;
				//use current row to eliminate column entries in all other
				//rows not equal to current row
				performRowEliminations(i);
				rowOpsPerformed++;
			}
			//if a swap didn't happen it means the column had all zero entries
			//time to offset to the next column over and try again
			else {
				offset++;
			}
		}
	}
	cout << "Row operations complete." << endl;
	cout << *this;
}

//tries to swap target row with a row beneath it, j, if
//the [j][i + offset] value is not zero
void Matrix::swapIfAble(int targetRow, int offset) {
	Rational zero(0);
	for (int j = targetRow + 1; j < rows; j++) {
		if ((*this)[j][targetRow + offset] != zero) {
			swapRows(targetRow, j);
			cout << "Swapping row " << targetRow + 1 << " with row " 
				<< j + 1 << endl;
			cout << *this;
			break;
		}
	}
}

//performs eliminations of all other rows using the target row
//and prints out results to console
//auxiliary function for rref
void Matrix::performRowEliminations(int targetRow) {
	for (int k = 0; k < rows; k++) {
		if (k != targetRow) {
			rowEliminate(targetRow, k);
			cout << "Eliminating column entry in row " << k + 1
				<< " using row " << targetRow + 1 << endl;
			cout << *this;
		}
	}
}

//prints out matrix to the console
ostream & operator<<(ostream & lhs, Matrix & rhs) {
	int rows = rhs.getRows();
	int cols = rhs.getCols();

	lhs << "Target matrix composition:" << endl;
	for (int i = 0; i < (NUM_PADDING + DEN_PADDING + 1 + VAL_PADDING) * 
			(cols) + 1; i++) {
		lhs << DELIM;
	}
	lhs << endl << endl << right;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			lhs << rhs[i][j];
			for (int i = 0; i < VAL_PADDING; i++) {
				lhs << " ";
			}
		}
		lhs << endl << endl;
	}
	lhs << endl;
	return lhs;
}

//reads matrix from file
fstream & operator>>(fstream & lhs, Matrix & rhs) {
	//file should be formatted as per the following:
	// numRows  numCols
	// (matrix contents here)
	
	int numRows, numCols;
	lhs >> numRows >> numCols;

	Matrix tempMatrix(numRows, numCols);
	Rational tempRational(0);
	for (int i = 0; i < numRows; i++) {
		for (int j = 0; j < numCols; j++) {
			lhs >> tempRational;
			tempMatrix[i][j] = tempRational;
		}
	}
	rhs = tempMatrix;
	return lhs;
}