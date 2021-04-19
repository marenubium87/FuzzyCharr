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
using std::internal;

template <typename T>
class Simpletron {
public:
	Simpletron();

	//prints out all registers, also prints memory in array format
	void print();

	//loads program into memory array
	void loadProgram(string fileName);

	//executes program already stored in memory array (not input file!)
	void executeProgram();

private:
	T accum;
	int instructCounter;
	T instructRegister;
	T operCode;
	T operand;
	T memArr[10][10];

	T haltCode;

	typedef enum errorCode {NOMINAL, INSTRUCTION_OUT_OF_BOUNDS, 
		INVALID_OPCODE, VAL_UNDERFLOW, VAL_OVERFLOW,
		ACC_UNDERFLOW, ACC_OVERFLOW, DIV_BY_ZERO
	} ErrorCode;

	//meta operations
	//reads next SML instruction from memory array
	T fetch();
	//determines operCode and operand
	int decode(T instruction);
	//executes instruction based on operCode and operand
	int execute();

	//operations
	int read();
	int write();
	int load();
	int store();
	int add();
	int subtract();
	int divide();
	int multiply();
	int branch();
	int branchNeg();
	int branchZero();
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
		cout << "+" << setw(4);
	}
	else {
		cout << setw(5);
	}
	cout << setfill('0') << accum;
	cout << "\t  Instruction:  " << setw(2) << instructCounter << endl;
	cout << "Register:     ";
	if (instructRegister >= 0) {
		cout << "+" << setw(4);
	}
	else {
		cout << setw(5);
	}
	cout << setfill('0') << instructRegister << "  -->  " <<
		"operCode:  " << setw(2) << setfill('0') << operCode <<
		"  operand:  " << setw(2) << setfill('0') << operand << endl << endl;
	cout << "**Memory**" << endl << endl << 
		"        0      1      2      3      4      5" << 
		"      6      7      8      9" << endl;
	for (int i = 0; i < 10; i++) {
		cout << setw(2) << setfill('0') << 10 * i << "  ";
		for (int j = 0; j < 10; j++) {
			if (memArr[i][j] >= 0) {
				cout << "+" << setw(4);
			}
			else {
				cout << setw(5);
			}
			cout << internal << setfill('0') << memArr[i][j] << "  ";
		}
		cout << endl;
	}
	cout << endl << endl;
}

template <typename T>
void Simpletron<T>::loadProgram(string fileName) {
	fstream input(fileName, std::ios::in);
	int i = 0;
	while (!input.eof()) {
		input >> memArr[i / 10][i % 10];
		i++;
	}
	input.close();
}

//executes program already stored in memory array (not input file!)
template <typename T>
void Simpletron<T>::executeProgram() {
	int status = NOMINAL;
	while (operCode != haltCode && status == NOMINAL) {
		print();
		status = decode(fetch());
		if (status == 0) {
			status = execute();
		}
		
		if (status != 0) {
			cout << "**Execution abnormally terminated!" << endl;
			system("pause");
			return;
		}
		system("pause");
		instructCounter++;
	}
}

//reads next SML instruction from memory array
template <typename T>
T Simpletron<T>::fetch() {
	
	return memArr[instructCounter / 10][instructCounter % 10];
}

//determines operCode and operand
//returns 0 if instruction is valid, 1 otherwise
template <typename T>
int Simpletron<T>::decode(T instruction) {
	if (instruction < -9999 || instruction > 9999) {
		cout << "Fatal error:  Instruction not in bounds!" << endl;
		return INSTRUCTION_OUT_OF_BOUNDS;
	}

	operCode = instruction / 100;
	operand = instruction % 100;
	return NOMINAL;
}

//executes instruction based on operCode and operand
//returns true if operation was successfully performed, false otherwise
template <typename T>
int Simpletron<T>::execute() {
	switch (operCode) {
	case 10:
		return read();
	case 11:
		return write();
	case 20:
		return load();
	case 21:
		return store();
	case 30:
		return add();
	case 31:
		return subtract();
	case 32:
		return divide();
	case 33:
		return multiply();
	case 40:
		return branch();
	case 41:
		return branchNeg();
	case 42:
		return branchZero();
	case 43:
		cout << "Halt operation detected, program complete." << endl;
		return NOMINAL;
	default:
		cout << "Error!  Invalid operation code!" << endl;
		return INVALID_OPCODE;
	}
}

//reads a value from the keyboard and places it into location operand
template <typename T>
int Simpletron<T>::read() {
	cout << "Enter a value.  ";
	cin >> memArr[operand / 10][operand % 10];
	cin.ignore();
	if (memArr[operand / 10][operand % 10] < -9999) {
		cout << "Error: value underflow!" << endl;
		return VAL_UNDERFLOW;
	}
	else if (memArr[operand / 10][operand % 10] > 9999) {
		cout << "Error: value overflow!" << endl;
		return VAL_OVERFLOW;
	}
	return NOMINAL;
}

//writes value from location operand to the console
template <typename T>
int Simpletron<T>::write() {
	cout << "Result is ";
	if (memArr[operand / 10][operand % 10] >= 0) {
		cout << "+" << setw(4);
	}
	else {
		cout << setw(5);
	}
	cout << setfill('0') << memArr[operand / 10][operand % 10]
		<< endl;
	return NOMINAL;
}

//loads value from operand into accumulator
template <typename T>
int Simpletron<T>::load() {
	cout << "Loading value into accumulator... " << endl;
	accum = memArr[operand / 10][operand % 10];
	return NOMINAL;
}

//stores value from accumulator to operand
template <typename T>
int Simpletron<T>::store() {
	cout << "Storing value from accumulator... " << endl;
	memArr[operand / 10][operand % 10] = accum;
	return NOMINAL;
}

//adds operand to accum, updates accum
template <typename T>
int Simpletron<T>::add() {
	cout << "Adding accumulator by operand..." << endl;
	accum += memArr[operand / 10][operand % 10];
	if (accum < -9999) {
		cout << "Error: accumulator underflow!" << endl;
		return ACC_UNDERFLOW;
	}
	else if (accum > 9999) {
		cout << "Error: accumulator overflow!" << endl;
		return ACC_OVERFLOW;
	}
	return NOMINAL;
}

//subtracts operand from accum, updates accum
template <typename T>
int Simpletron<T>::subtract() {
	cout << "Subtracting accumulator by operand..." << endl;
	accum -= memArr[operand / 10][operand % 10];
	if (accum < -9999) {
		cout << "Error: accumulator underflow!" << endl;
		return ACC_UNDERFLOW;
	}
	else if (accum > 9999) {
		cout << "Error: accumulator overflow!" << endl;
		return ACC_OVERFLOW;
	}
	return NOMINAL;
}

//divides operand from accum, updates accum
template <typename T>
int Simpletron<T>::divide() {
	cout << "Dividing accumulator by operand..." << endl;
	if (memArr[operand / 10][operand % 10] == 0) {
		cout << "Error: division by zero detected!" << endl;
		return DIV_BY_ZERO;
	}
	accum /= memArr[operand / 10][operand % 10];
	
	return NOMINAL;
}

//multiplies accum by operand, updates accum
template <typename T>
int Simpletron<T>::multiply() {
	cout << "Multiplying accumulator by operand..." << endl;
	accum *= memArr[operand / 10][operand % 10];
	if (accum < -9999) {
		cout << "Error: accumulator underflow!" << endl;
		return ACC_UNDERFLOW;
	}
	else if (accum > 9999) {
		cout << "Error: accumulator overflow!" << endl;
		return ACC_OVERFLOW;
	}
	return NOMINAL;
}

//branch to operand
template <typename T>
int Simpletron<T>::branch() {
	cout << "Branching..." << endl;
	//-1 accounts for the instructCounter incrementing at the end of a cycle
	instructCounter = operand - 1;
	return NOMINAL;
}

//branch to operand if accum is negative
template <typename T>
int Simpletron<T>::branchNeg() {
	if (accum < 0) {
		cout << "Accum is negative, branching..." << endl;
		//-1 accounts for the instructCounter incrementing at the end of a cycle
		instructCounter = operand - 1;
	}
	else {
		cout << "Accum not negative, continuing..." << endl;
	}
	return NOMINAL;
}

//branch to operand if accum is zero
template <typename T>
int Simpletron<T>::branchZero() {
	if (accum == 0) {
		cout << "Accum is zero, branching..." << endl;
		//-1 accounts for the instructCounter incrementing at the end of a cycle
		instructCounter = operand - 1;
	}
	else {
		cout << "Accum not zero, continuing..." << endl;
	}
	return NOMINAL;
}