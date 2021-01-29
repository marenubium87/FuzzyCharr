//Aerie, CS122 PA4
//24 Jan 2021

#include "FitnessAppWrapper.h"

int main() {
	
	fstream input, output;
	input.open("dietPlans.txt", std::ios::in);
	output.open("exercisePlans.txt", std::ios::out);

	DietPlan d1, d2;
	input >> d1 >> d2;
	//d1.editGoal();
	//cout << d1 << endl << d2 << endl;
	DietPlanList l1;
	l1.append(d1);
	l1.append(d2);
	l1.append(d1);
	l1.clear();


	system("pause");
	return 0;
}