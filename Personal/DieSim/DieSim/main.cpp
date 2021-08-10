#include "DieSim.h"

int main() {

	srand((unsigned int)time(NULL));
	vector<int> diePool = {10, 10, 10, 10, 10, 10};
	SimulationRun * pSimulation = nullptr;

	//initializes simulation mode names
	enum SimMode {noMode, numSuccessesNoBotch};
	int simMode = noMode;

	
	RollAnalysis * a = new RollAnalysis(diePool, 6, 4);
	for (int i = 0; i < 5; i++) {
		a->roll();
		cout << "Get success returned " << a->getSuccesses() << endl;
		cout << "Get fails returned " << a->getFails() << endl;
		cout << "Get net returned " << a->getNetSuccesses() << endl;
	}
	

	/*
	int choice = 0;
	while (choice != 4) {
		printDiePool(diePool);
		displayMainMenu();
		cin >> choice;
		cin.ignore(1000, '\n');
		switch (choice) {
		case 1:
			adjustDiePool(diePool);
			break;
		case 2:
			//set simulation mode
			
			setSimMode(simMode);
			pSimulation = makeNewSim(simMode);
			break;
		case 3:
			//set simulation parameters
			break;
		case 4:
			//run simulation
			break;
		default:
			cout << string(100, '\n');
			cout << "Please enter a valid option.\n\n\n";
		}
	}
	*/

	return 0;
}