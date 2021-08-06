#include "DieSim.h"

void displayMainMenu() {
	cout << "Select an option" << endl
		<< " 1.  Adjust die pool" << endl
		<< " 2.  do something else " << endl
		<< " 3.  do yet another thing " << endl
		<< " 4.  do yet another other thing" << endl
		<< endl;
}


void printDiePool(vector<int> & diePool) {
	cout << "Current die pool:" << endl << "  ";
	for (int n : diePool) {
		cout << 'D' << n << " ";
	}
	cout << endl << endl;
}

void adjustDiePool(vector<int> & diePool) {
	cout << string(100, '\n');
	cout << "Enter new dice for die pool, separated by spaces." << endl
		<< "(enter # of faces for each die, e.g. for a D10, type 10 only.)"
		<< endl << endl;

	diePool.clear();

	string tempStr;
	getline(cin, tempStr);
	stringstream s(tempStr);

	int nextDie;
	while (s >> nextDie) {
		diePool.push_back(nextDie);
	}

}