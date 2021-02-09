//header for matrix class

#pragma once

#include <iostream>
#include <cmath>
#include <string>
#include "rational.h"

using std::cin;
using std::cout;
using std::istream;
using std::ostream;
using std::fstream;
using std::endl;
using std::string;

class Matrix {
public:
	//initializes matrix with number of rows and cols from heap
	Matrix(int rows = 1, int cols = 1);
	~Matrix() { delete arr; }

	unsigned int getRows() const { return rows; }
	unsigned int getCols() const { return cols; }

	//overloaded get/set cell fcns
	//returns the rational at the cell (row, col) for the matrix
	Rational & cell(unsigned int row, unsigned int col) const;
	//sets the rational at the cell (row, col) to target
	void cell(unsigned int row, unsigned int col, Rational const & target);

private:
	int rows;
	int cols;
	//pointer to the [0][0] element
	Rational * arr;
};

//prints out matrix to the console
ostream & operator<<(ostream & lhs, Matrix rhs);