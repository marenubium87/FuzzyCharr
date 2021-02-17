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
void Matrix::normalizeRow(int target) {
	int i = 0;
	//start in target row
	Rational * targetRowStart = arr + target * cols;

	while (targetRowStart[i].getNum() == 0 && i < cols) {
		i++;
	}

	//i is at first entry in row that is not zero
	Rational normalizationCoeff(0);
	if (i < cols) {
		//sets normalization coefficient to the value that will 
		//multiply by the first nonzero entry in the row to equal 1
		
		normalizationCoeff.setSign(targetRowStart[i].getSign());
		normalizationCoeff.setNum(targetRowStart[i].getDen());
		normalizationCoeff.setDen(targetRowStart[i].getNum());
	}
	for (; i < cols; i++) {
		targetRowStart[i] = targetRowStart[i] * normalizationCoeff;
	}
}

//swaps row a and row b in matrix
//row index starts with 0, not 1
void Matrix::swapRows(int a, int b) {
	if (!(a < rows) || !(b < rows)) {
		cout << "Error in fcn: swapRows" << endl;
		cout << "Invalid arguments for row swap targets!" << endl;
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
	if (!(a < rows) || !(b < rows)) {
		cout << "Error in fcn: rowEliminate" << endl;
		cout << "Invalid arguments row elimination targets!" << endl;
		return;
	}
	else if (a == b) {
		cout << "Error in fcn: rowEliminate" << endl;
		cout << "Designated row and target row cannot be the same!";
		cout << endl;
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
		cout << endl;
		return;
	}

	//if code execution makes it to here, i is at index of first nonzero
	//element of row a, so start row elimination process
	Rational * startRowB = arr + b * cols;
	//determine multiplier to make the entry in row b zero
	Rational multiplier = startRowB[i] / startRowA[i];
	for (; i < cols; i++) {
		startRowB[i] = startRowB[i] - multiplier * startRowA[i];
	}
}

//prints out matrix to the console
ostream & operator<<(ostream & lhs, Matrix & rhs) {
	int rows = rhs.getRows();
	int cols = rhs.getCols();

	cout << "Target matrix composition:" << endl;
	for (int i = 0; i < (NUM_PADDING + DEN_PADDING + 1 + VAL_PADDING) * 
			(cols) + 1; i++) {
		cout << DELIM;
	}
	cout << endl << right;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cout << rhs[i][j];
			for (int i = 0; i < VAL_PADDING; i++) {
				cout << " ";
			}
		}
		cout << endl;
	}
	return lhs;
}

//test function to test copy constructor and by extension private member fcns
void doThings(Matrix original) {
	Rational target(-6, 2);
	cout << original;
	cout << original;
	original.reduce();
	cout << original;
}