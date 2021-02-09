//source for matrix class

#include "matrix.h"

Matrix::Matrix(int rows, int cols) {
	arr = new Rational[rows * cols];
	for (int i = 0; i < rows * cols; i++) {
		arr[i] = 0;
	}
}

//returns the rational at the cell (row)(col) for the matrix
Rational & Matrix::cell(unsigned int row, unsigned int col) const {
	return arr[row * cols + col];
}

//sets the rational at the cell (row, col) to target
void Matrix::cell(unsigned int row, unsigned int col, Rational const & target) {
	arr[row * cols + col] = target;
}

//prints out matrix to the console
//ostream & operator<<(ostream & lhs, Matrix rhs) {
//	int rows = rhs.getRows();
//	int cols = rhs.getCols();
//
//	cout << "Target matrix composition:" << endl << endl;
//	for (int i = 0; i < rows; i++) {
//		for (int j = 0; j < cols; j++) {
//			//cout <<
//		}
//		cout << endl;
//	}
//
//
//}