#include "DieSim.h"

int main() {
	vector<int> diePool = {10, 10, 10, 10, 10, 10, 10, 10};

	

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
			break;
		case 3:
			break;
		case 4:
			break;
		default:
			cout << string(100, '\n');
			cout << "Please enter a valid option.\n\n\n";
		}
	}

	return 0;
}