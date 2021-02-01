//header for exercise plan class

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
using std::getline;

class ExercisePlan {
public:
	//constructors, destructors
	ExercisePlan();
	ExercisePlan(string newName, int newGoal, string newDate);
	ExercisePlan(ExercisePlan const & original);
	~ExercisePlan() {}
	ExercisePlan & operator=(ExercisePlan const & rhs);

	//accessors, mutators
	void setGoal(int const newGoal) { goal = newGoal; }
	void setName(string const newName) { name = newName; }
	void setDate(string const newDate) { date = newDate; }

	int getGoal(void) const { return goal; }
	string getName(void) const { return name; }
	string getDate(void) const { return date; }

	//other member fcns
	//prompts user for new goal, changes goal accordingly, displays to screen
	void editGoal(void);

private:
	int goal;
	string name;
	string date;
};

//stream insertion operator, writing to console
ostream & operator<<(ostream & lhs, ExercisePlan const & rhs);

//stream insertion operator, writing to file
ofstream & operator<<(ofstream & lhs, ExercisePlan & rhs);

//stream extraction operator, from file
fstream & operator>>(fstream & lhs, ExercisePlan & rhs);

//*******************************************************************

class ExercisePlanNode {
public:
	//constructors
	ExercisePlanNode();
	ExercisePlanNode(ExercisePlan newPlan, ExercisePlanNode * newNext = nullptr);

	//accessors, mutators
	ExercisePlan & getPlan(void) { return plan; }
	ExercisePlanNode * getNext(void) const { return pNext; }
	void setPlan(ExercisePlan const & newPlan) { plan = newPlan; }
	void setNext(ExercisePlanNode * const & newNext) { pNext = newNext; }

	//returns the plan's name in the current dietPlanNode
	string const getPlanName();

	//other methods
	//allows access to the editGoal fcn in DietPlan from this interface
	void editPlanGoal();

private:
	ExercisePlan plan;
	ExercisePlanNode * pNext;
};

//*******************************************************************

class ExercisePlanList {
public:
	//constructors, destructors
	ExercisePlanList();
	~ExercisePlanList();
	ExercisePlanList(ExercisePlanList const & original);
	ExercisePlanList & operator=(ExercisePlanList const & original);

	//member fcns
	//takes newPlan, creates an ExercisePlanNode using its data
	//appends it to the list and updates the tail pointer
	void append(ExercisePlan const & newPlan);

	//returns 1 if list is empty, 0 else
	int isEmpty();
	//prints out contents of list to console
	void print() const;
	//stores the contents of the list to file
	void store(fstream & outputFile) const;

	//searches list sequentially for first node whose plan's name
	//(day of the week) matches nameQuery exactly,
	//and allows the user to modify the goal steps for that day
	void search(string const & nameQuery);

private:
	//marks first and last elements of list
	//both nullptr if list is empty
	ExercisePlanNode * pHead;
	ExercisePlanNode * pTail;

	//removes the first ExercisePlanNode in the list
	//does nothing if list is already empty
	void deleteAtFront();

	//clears the contents of an entire list, freeing memory
	void clear();
};