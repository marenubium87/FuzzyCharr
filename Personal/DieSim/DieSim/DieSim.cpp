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

//completely rewrites elements of die pool based on user input
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

void displayModes(void) {
	cout << " 1.  Num successes, no botch" << endl;
}

void setSimMode(int & simMode) {
	cout << "Select a simulation mode, then press enter: " << endl;
	displayModes();
	cin >> simMode;
	cin.ignore(1000, '\n');
}

//creates new simulation object based on user-selected simulation mode
SimulationRun * makeNewSim(int simMode) {
	switch (simMode) {
	case 1:
		return new SimNumSuccesses();
		break;
	default:
		return nullptr;
		break;
	}
}


RollAnalysis::RollAnalysis(vector<int> & diePool,
	int inputSuccThresh, int inputFailThresh) : rDiePool(diePool)
{
	successThreshold = inputSuccThresh;
	failThreshold = inputFailThresh;
}

//rolls each die in die pool, assumes faces are 1 - n
//where n is value loaded into diePool vector
void RollAnalysis::roll() {
	resultPool.clear();
	for (int & die : rDiePool) {
		resultPool.push_back(rand() % die + 1);
	}
}

int RollAnalysis::getSuccesses() {
	int successes = 0;
	for (int & die : resultPool) {
		if (die >= successThreshold) {
			successes++;
		}
	}
	return successes;
}

int RollAnalysis::getFails() {
	int fails = 0;
	for (int die : resultPool) {
		if (die <= failThreshold) {
			fails++;
		}
	}
	return fails;
}

//successes minus fails, clamped at zero
int RollAnalysis::getNetSuccesses() {
	int a = getSuccesses() - getFails();
	a = a >= 0 ? a : 0;
	return a;
}