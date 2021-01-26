//source for diet plan class

#include "DietPlan.h"

//*******************************************************************

//DietPlan Class
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
fstream & operator>>(fstream & lhs, DietPlan & rhs) {
	string tempStr = "";
	int tempInt = 0;

	//gets the next line that isn't empty
	do {
		getline(lhs, tempStr);
	} while (tempStr == "" && !lhs.eof());
	
	//if we hit eof here return and give an error message
	if (lhs.eof()) {
		cout << "Error: unexpected end-of-file when reading from file" << endl;
		cout << "Diet plan(s) may not have been read successfully!";
		cout << endl << endl;
		return lhs;
	}

	rhs.setName(tempStr);
	lhs >> tempInt;
	rhs.setGoal(tempInt);
	//consumes newline character from above >> call
	lhs >> std::ws;
	getline(lhs, tempStr);
	rhs.setDate(tempStr);
	
	return lhs;
}

//*******************************************************************

//DietPlanNode class
//default constructor
DietPlanNode::DietPlanNode() {

}
//constructor with args
DietPlanNode::DietPlanNode(DietPlan newPlan, DietPlanNode * pNext = nullptr) {

}