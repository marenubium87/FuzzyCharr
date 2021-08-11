#include "DieSim.h"

void displayMainMenu() {
	cout << "Select an option" << endl
		<< " 1.  Adjust die pool" << endl
		<< " 2.  Set simulation type " << endl
		<< " 3.  Display/change simulation parameters " << endl
		<< " 4.  Execute simulation" << endl
		<< " 5.  Exit "
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

void displayModesSelection(void) {
	cout << " 1.  Num successes, no botch" << endl
		<< "2.  This is like, a placeholder " << endl
		<< endl;
}

void setSimMode(int & simMode) {
	cout << "Select a simulation mode, then press enter: " << endl;
	displayModesSelection();
	cin >> simMode;
	cin.ignore(1000, '\n');
}

//methods for RollAnalysis class go here
//*******************************************//

RollAnalysis::RollAnalysis(vector<int> & diePool) : rDiePool(diePool)
{
	successThreshold = 0;
	failThreshold = 0;
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

//botch is zero successes and one or more fails
bool RollAnalysis::isBotch() {
	return (getSuccesses() == 0 && getFails() > 0);
}

//methods for SimulationRun class go here
//*******************************************//

SimulationRun::SimulationRun(vector<int> & diePool) : rDiePool(diePool) {
	analysis = new RollAnalysis(diePool);
}

//creates new simulation object based on user-selected simulation mode
SimulationRun * makeNewSim(int simMode, vector<int> & diePool) {
	switch (simMode) {
	case netSuccessesNoBotch:
		return new SimNumSuccesses(diePool);
		break;
	default:
		return nullptr;
		break;
	}
}

//methods for SimNumSuccesses derived class go here
//*******************************************//

SimNumSuccesses::SimNumSuccesses(vector<int> & diePool) :
	SimulationRun(diePool)
{

}

void SimNumSuccesses::displayConfig(void) {
	cout << "Current mode:  net successes, no botch" << endl
		<< " Success threshold:  >= " << analysis->getSuccessThreshold()
		<< endl;

	cout << " Fail threshold:  <= " << analysis->getFailThreshold()
		<< endl;
	cout << " Number of trials:  " << numTrials << endl << endl;
}

void SimNumSuccesses::displayConfigSettings(void) {
	cout << "1.  Change success threshold " << endl
		<< "2.  Change fail threshold " << endl;

	cout << "3.  Change number of trials " << endl
		<< "4.  Exit" << endl << endl;
}

void SimNumSuccesses::setConfig(void) {
	int choice = 0;
	int newVal = 0;
	cout << "Make a selection:  ";
	cin >> choice;
	cin.ignore(1000, '\n');
	if (choice > 0 && choice < 4) {
		cout << endl << endl << "Enter a new value.  ";
		cin >> newVal;
		cin.ignore(1000, '\n');
	}

	switch (choice) {
	case 1:
		analysis->setSuccessThreshold(newVal);
		break;
	case 2:
		analysis->setFailThreshold(newVal);
		break;
	case 3:
		numTrials = newVal;
		break;
	default:
		break;
	}
}

void SimNumSuccesses::commenceSimulation(void) {
	cumResults.clear();

	//initialize results table
	for (unsigned int i = 0; i <= rDiePool.size(); i++) {
		cumResults.push_back(vector<int>());
		cumResults[i].push_back(i);
		cumResults[i].push_back(0);
	}

	int result = 0;
	for (int i = 1; i <= numTrials; i++) {
		analysis->roll();
		result = analysis->getSuccesses();
		cumResults[result][1]++;
	}
	cout << endl << endl;
	cout << "x=n      prob" << endl;
	for (int i = 0; i <= rDiePool.size(); i++) {
		cout << i << setw(8) << cumResults[i][1] << endl;
	}
}

