//Aerie, CS122 PA4
//24 Jan 2021

#include "FitnessAppWrapper.h"

int main() {
	
	fstream input, output;
	input.open("dietPlans.txt", std::ios::in);
	output.open("exercisePlans.txt", std::ios::out);

	DietPlan d1, d2;
	input >> d1;
	d1.editGoal();
	output << d1;


	system("pause");
	return 0;
}