//source for fitness app wrapper

#include "FitnessAppWrapper.h"

//default constructor
FitnessAppWrapper::FitnessAppWrapper() {
	dietPlanFile.open("dietPlans.txt", std::ios::in);
	exercisePlanFile.open("exercisePlans.txt", std::ios::in);
}

//destructor
FitnessAppWrapper::~FitnessAppWrapper() {
	dietPlanFile.close();
	exercisePlanFile.close();
}

//starts main application
void FitnessAppWrapper::runApp(void) {
	
	int selection = 0;
	do {
		system("cls");
		displayMenu();
		
		cin >> selection;
		system("cls");
		switch (selection) {
		case 1:
			loadWeeklyDiet();
			cout << "Loaded weekly diet plans from file.";
			break;
		case 2:
			loadWeeklyExercise();
			cout << "Loaded weekly exercise plans from file.";
			break;
		case 3:
			storeDiet();
			cout << "Weekly diet plans stored to file.";
			break;
		case 4:
			storeExercise();
			cout << "Weekly exercise plans stored to file.";
			break;
		case 5:
			printDiet();
			break;
		case 6:
			printExercise();
			break;
		case 7:
			searchDiet();
			break;
		case 8:
			searchExercise();
			break;
		case 9:
			cout << "Saving your plans to file... " << endl;
			storeDiet();
			storeExercise();
			cout << "Okay, bai.";
			break;
		default:
			cout << "Please enter a valid input.";
		}
		cout << endl << endl;
		system("pause");

	} while (selection != 9);
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
void FitnessAppWrapper::loadDailyPlan(DietPlan & plan) {
	dietPlanFile >> plan;
}

//reads one ExercisePlan record from the given stream
void FitnessAppWrapper::loadDailyPlan(ExercisePlan & plan) {
	exercisePlanFile >> plan;
}

//reads all daily diet plans from file, calls loadDailyPlan
//preconditon - file is already open
void FitnessAppWrapper::loadWeeklyDiet() {
	DietPlan tempPlan;
	for (int i = 0; i < 7; i++) {
		loadDailyPlan(tempPlan);
		weeklyDietPlan.append(tempPlan);
	}
}

//reads all daily exercise plans from file, calls loadDailyExercisePlan
//precondition - file is already open
void FitnessAppWrapper::loadWeeklyExercise() {
	ExercisePlan tempPlan;
	for (int i = 0; i < 7; i++) {
		loadDailyPlan(tempPlan);
		weeklyExercisePlan.append(tempPlan);
	}
}

//prints all daily diet plans to console
void FitnessAppWrapper::printDiet() {
	weeklyDietPlan.print();
}

//prints all daily exercise plans to console
void FitnessAppWrapper::printExercise() {
	weeklyExercisePlan.print();
}

//stores all daily diet plans to file
void FitnessAppWrapper::storeDiet() {
	if (dietPlanFile.is_open()) {
		dietPlanFile.close();
	}
	dietPlanFile.open("dietPlans.txt", std::ios::out);
	weeklyDietPlan.store(dietPlanFile);
}

//stores all daily exercise plans to file
void FitnessAppWrapper::storeExercise() {
	if (exercisePlanFile.is_open()) {
		exercisePlanFile.close();
	}
	exercisePlanFile.open("exercisePlans.txt", std::ios::out);
	weeklyExercisePlan.store(exercisePlanFile);
}

//wrapper to search through DietPlanList
void FitnessAppWrapper::searchDiet() {
	string inputStr = "";
	cout << "Enter the name of the plan you wish to edit:  ";
	cin >> inputStr;
	weeklyDietPlan.search(inputStr);
}

//wrapper to search through ExercisePlanList
void FitnessAppWrapper::searchExercise() {
	string inputStr = "";
	cout << "Enter the name of the plan you wish to edit:  ";
	cin >> inputStr;
	weeklyExercisePlan.search(inputStr);
}