//header for PA7

#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>
#include <fstream>

using std::cin;
using std::cout;
using std::getline;
using std::string;
using std::istream;
using std::ostream;
using std::endl;
using std::fstream;
using std::setw;
using std::setfill;


template <typename T>
class Simpletron {
public:
	Simpletron();

	//prints out all registers, also prints memory in array format
	void print();

	//loads program into memory array
	void loadProgram(string fileName);

	void executeProgram();

private:
	T accum;
	int instructCounter;
	T instructRegister;
	T operCode;
	T operand;
	T memArr[10][10];

	T haltCode;

	//meta operations
	//reads next SML instruction from memory array
	void fetch();
	//determines operCode and operand
	void decode();
	//executes instruction based on operCode and operand
	void execute();

	//operations
	void read();
	void write();
	void load();
	void store();

	void add();
	void subtract();
	void divide();
	void multiply();

	void branch();
	void branchNeg();
	void branzhZero();

};

template <typename T>
Simpletron<T>::Simpletron() {
	accum = 0;
	instructCounter = 0;
	instructRegister = 0;
	operCode = 0;
	operand = 0;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			memArr[i][j] = 0;
		}
	}
	haltCode = 43;
}

//prints out all registers and memory in array format
template <typename T>
void Simpletron<T>::print() {
	system("cls");
	cout << "    SIMPLETRON STATUS" << endl << endl;
	cout << "**Registers**" << endl << endl;
	cout << "Accumulator:  ";
	if (accum >= 0) {
		cout << "+";
	}
	cout << setw(4) << setfill('0') << accum;
	cout << "\t  Instruction:  " << setw(2) << instructCounter << endl;
	cout << "Register:     ";
	if (instructRegister >= 0) {
		cout << "+";
	}
	cout << setw(4) << instructRegister << "  -->  " <<
		"operCode:  " << setw(2) << setfill('0') << operCode <<
		"  operand:  " << setw(2) << setfill('0') << operand << endl << endl;
	cout << "**Memory**" << endl << endl << 
		"        0      1      2      3      4      5" << 
		"      6      7      8      9" << endl;
	for (int i = 0; i < 10; i++) {
		cout << setw(2) << setfill('0') << 10 * i << "  ";
		for (int j = 0; j < 10; j++) {
			if (memArr[i][j] >= 0) {
				cout << "+";
			}
			cout << setw(4) << setfill('0') << memArr[i][j] << "  ";
		}
		cout << endl;
	}
}

template <typename T>
void Simpletron<T>::loadProgram(string fileName) {
	fstream input(fileName, std::ios::in);
	int i = 0;
	while (!input.eof()) {
		input >> memArr[i / 10][i % 10];
		i++;
	}
}