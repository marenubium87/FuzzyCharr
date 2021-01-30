//source for fitness app wrapper

#include "FitnessAppWrapper.h"

//starts main application
void FitnessAppWrapper::runApp(void) {
	system("cls");
	displayMenu();
	int selection = 0;
	cin >> selection;
	//consumes newline character
	cin >> std::ws;
}

//displays menu options to console
void FitnessAppWrapper::displayMenu(void) {
	cout << "Make a selection from the options below:" << endl << endl;
	cout << "1.  Load weekly diet plan from file" << endl;
	cout << "2.  Load weekly exercise plan from file" << endl;
	cout << "3.  Store weekly diet plan to file" << endl;
	cout << "4.  Store weekly exercise plan to file" << endl;
	cout << "5.  Display weekly diet plan to screen" << endl;
	cout << "6.  Display weekly exercise plan to screen" << endl;
	cout << "7.  Edit daily diet plan" << endl;
	cout << "8.  Edit daily exercise plan" << endl;
	cout << "9.  Exit" << endl << endl;
}

//reads one DietPlan record from the given stream
//precondition - file is already open
void FitnessAppWrapper::loadDailyPlan(fstream & fileStream, DietPlan & plan) {
	fileStream >> plan;
}

//reads in all seven daily plans from the given stream
//calls loadDailyPlan
//preconditon - file is already open
void FitnessAppWrapper::loadWeeklyPlan(fstream & fileStream) {
	DietPlan tempPlan;
	for (int i = 0; i < 7; i++) {
		loadDailyPlan(fileStream, tempPlan);
		weeklyDietPlan.append(tempPlan);
	}
}

