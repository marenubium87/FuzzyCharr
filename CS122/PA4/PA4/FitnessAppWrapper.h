//header for fitness app wrapper

#include "ExercisePlan.h"
#include "DietPlan.h"

class FitnessAppWrapper {
public:
	//constructors, destructors
	FitnessAppWrapper();
	~FitnessAppWrapper();

	//starts main application
	void runApp(void);

	//displays menu options to console
	void displayMenu(void);

	//reads all diet plans, calls loadDailyPlan
	//preconditon - file is already open
	void loadWeeklyDiet();

	//reads all exercise plans, calls loadDailyPlan
	//precondition - file is already open
	void loadWeeklyExercise();

	//prints all daily plans to the console
	void printDiet();
	void printExercise();

	//stores all daily plans to file
	//closes file if it is open and reopens it for writing
	void storeDiet();
	void storeExercise();

	//wrapper to search through lists
	void searchDiet();
	void searchExercise();

private:
	fstream dietPlanFile;
	fstream exercisePlanFile;
	DietPlanList weeklyDietPlan;
	ExercisePlanList weeklyExercisePlan;

	//reads one record from the given stream
	void loadDailyPlan(DietPlan & plan);
	void loadDailyPlan(ExercisePlan & plan);
};