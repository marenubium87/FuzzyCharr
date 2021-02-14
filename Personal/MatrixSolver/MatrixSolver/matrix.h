//header for matrix class

//the delimiter char after "target matrix composition"
#define DELIM '-'
//padding between entries in the matrix
#define VAL_PADDING 4

#pragma once

#include <iostream>
#include <cmath>
#include <string>
#include <iomanip>
#include "rational.h"

using std::cin;
using std::cout;
using std::istream;
using std::ostream;
using std::fstream;
using std::endl;
using std::string;
using std::setw;
using std::left;
using std::right;


class Matrix {
public:
	//initializes matrix with number of newRows and newCols from heap
	//if no arguments, creates a "null" matrix with no memory allocated
	//for the array
	Matrix(int newRows = 0, int newCols = 0);
	//copy constructor
	Matrix(Matrix const & original);
	//destructor
	~Matrix() {
		delete[] arr; 
	}
	//overloaded assignment operator
	Matrix & operator=(Matrix const & rhs);

	int getRows() const { return rows; }
	int getCols() const { return cols; }

	//overloaded [] operator for 2D matrix operations
	Rational * operator[](int i);

	//overloaded get/set cell fcns
	//returns the rational at the cell (row, col) for the matrix
	Rational & cell(int row, int col) const;
	//sets the rational at the cell (row, col) to target
	void cell(int row, int col, Rational const & target);

	//calls Rational's reduce on every entry of the matrix
	void reduce();

	//multiplies target row by coeff such that its first
	//nonzero element is equal to one
	void normalizeRow(int target);

	//swaps row a and row b in matrix
	//row index starts with 0, not 1
	void swapRows(int a, int b);

	//uses the first nonzero entry in row a to eliminate the entry
	//in the corresponding column in row b
	void rowEliminate(int a, int b);

private:
	int rows;
	int cols;
	//pointer to the [0][0] element
	Rational * arr;
};

//prints out matrix to the console
ostream & operator<<(ostream & lhs, Matrix & rhs);

//test function to test copy constructor and by extension private memeber fcns
void doThings(Matrix original);