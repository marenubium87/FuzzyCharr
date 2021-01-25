//source for diet plan class

#include "DietPlan.h"

//constructors for DietPlan
DietPlan::DietPlan() {
	name = "";
	goal = 0;
	date = "";
}

DietPlan::DietPlan(string newName, int newGoal, string newDate) {
	name = newName;
	goal = newGoal;
	date = newDate;
}
DietPlan::DietPlan(DietPlan const & original) {
	*this = original;
}

DietPlan & DietPlan::operator=(DietPlan const & rhs) {
	name = rhs.name;
	goal = rhs.goal;
	date = rhs.date;
	return *this;
}

//others
//prompts user for new goal, changes goal accordingly, displays to screen
void DietPlan::editGoal(void) {
	int input = 0;
	cout << "Type in a new goal calorie count (number):  ";
	cin >> input;
	goal = input;
	cout << "Your new plan:" << endl << endl << *this << endl;
	system("pause");
}

//stream insertion operator, writing to console
ostream & operator<<(ostream & lhs, DietPlan const & rhs) {
	lhs << rhs.getName() << endl << rhs.getGoal() << endl << rhs.getDate();
	return lhs;
}

//stream insertion operator, writing to file
ofstream & operator<<(ofstream & lhs, DietPlan const & rhs) {
	lhs << rhs.getName() << endl << rhs.getGoal() << endl << rhs.getDate();
	return lhs;
}

//stream extraction operator, from file
//fstream & operator>>(fstream & lhs, DietPlan & rhs) {
//
//}