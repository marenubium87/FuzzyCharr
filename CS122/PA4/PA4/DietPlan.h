//header for diet plan class

#include <iostream>
#include <string>
#include <fstream>

using std::cin;
using std::cout;
using std::istream;
using std::ostream;
using std::endl;
using std::string;
using std::fstream;
using std::ifstream;
using std::ofstream;

class DietPlan {
public:
	//constructors, destructors
	DietPlan();
	DietPlan(string newName, int newGoal, string newDate);
	DietPlan(DietPlan const & original);
	~DietPlan() {}
	DietPlan & operator=(DietPlan const & rhs);

	//accessors, mutators
	void setGoal(int const newGoal) { goal = newGoal; }
	void setName(string const newName) { name = newName; }
	void setDate(string const newDate) { date = newDate; }

	int getGoal(void) const { return goal; }
	string getName(void) const { return name; }
	string getDate(void) const { return date; }

	//others
	//prompts user for new goal, changes goal accordingly, displays to screen
	void editGoal(void);

private:
	int goal;
	string name;
	string date;
};

//stream insertion operator, writing to console
ostream & operator<<(ostream & lhs, DietPlan const & rhs);

//stream insertion operator, writing to file
ofstream & operator<<(ofstream & lhs, DietPlan & rhs);

//stream extraction operator, from file
//fstream & operator>>(fstream & lhs, DietPlan & rhs);