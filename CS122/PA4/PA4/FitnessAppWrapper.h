//header for fitness app wrapper

#include "ExercisePlan.h"
#include "DietPlan.h"

class FitnessAppWrapper {
public:
	//constructor
	FitnessAppWrapper(fstream newDietPlanFile, fstream newExercisePlanFile);



	//starts main application
	void runApp(void);

	//displays menu options to console
	void displayMenu(void);

	//reads one DietPlan record from the given stream
	//precondition - file is already open
	void loadDailyPlan(fstream & fileStream, DietPlan & plan);

	//reads one ExercisePlan record from the given stream
	//precondition - file is already open
	//void loadDailyPlan(fstream & fileStream, ExercisePlan & plan);

	//reads in all seven daily plans from the given stream
	//calls loadDailyPlan
	//preconditon - file is already open
	void loadWeeklyPlan(fstream & fileStream);

	//writes a daily plan to the screen
	void displayDailyPlan(DietPlan & plan);

	//writes a weekly plan to the screen; calls displayDailyPlan
	void displayWeeklyPlan(DietPlanList & weeklyDietPlan);

	//writes daily plan to file
	//precondition - file is already open
	void storeDailyPlan(fstream & fileStream, DietPlan & plan);

	//writes the weekly plan to file; calls storeDailyPlan
	//precondition - file is already open
	void storeWeeklyPlan(fstream & fileStream, DietPlan & plan);

private:
	fstream dietPlanFile;
	fstream exercisePlanFile;
	DietPlanList weeklyDietPlan;
	//ExercisePlanList weeklyExercisePlan;
};