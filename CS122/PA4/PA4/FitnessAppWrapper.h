//header for fitness app wrapper

#include "ExercisePlan.h"
#include "DietPlan.h"

class FitnessAppWrapper {
public:
	//default constructor
	FitnessAppWrapper();

	//starts main application
	void runApp(void);

	//displays menu options to console
	void displayMenu(void);

	//reads one DietPlan record from the given stream
	//precondition - file is already open
	void loadDailyPlan(DietPlan & plan);

	//reads one ExercisePlan record from the given stream
	//precondition - file is already open
	//void loadDailyPlan(ExercisePlan & plan);

	//reads in all seven daily diet plans from the given stream
	//calls loadDailyPlan
	//preconditon - file is already open
	void loadWeeklyDiet();

	//prints all seven daily plans to the console
	void printDiet();

	//write interface for search
	void searchDiet();

private:
	fstream dietPlanFile;
	fstream exercisePlanFile;
	DietPlanList weeklyDietPlan;
	//ExercisePlanList weeklyExercisePlan;
};