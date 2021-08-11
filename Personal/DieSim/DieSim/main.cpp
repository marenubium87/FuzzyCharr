#include "DieSim.h"

int main() {

	srand((unsigned int)time(NULL));
	vector<int> diePool = {10, 10, 10, 10, 10, 10};
	SimulationRun * pSimulation = nullptr;

	int simMode = noMode;

	int choice = 0;
	while (choice != 5) {
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
			pSimulation = makeNewSim(simMode, diePool);

			//invalid choice in makeNewSim reset pSimulation to nullptr
			//so reset simMode accordingly.
			if (!pSimulation) {
				simMode = noMode;
			}
			break;
		case 3:
			//change configs
			if (!pSimulation) {
				break;
			}
			pSimulation->displayConfig();
			pSimulation->displayConfigSettings();
			pSimulation->setConfig();

			break;
		case 4:
			if (!pSimulation) {
				break;
			}
			//run simulation
			pSimulation->commenceSimulation();
			break;
		default:
			cout << string(100, '\n');
			cout << "Please enter a valid option.\n\n\n";
		}
	}
	

	return 0;
}