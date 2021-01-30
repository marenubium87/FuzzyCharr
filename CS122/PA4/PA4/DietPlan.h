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
using std::getline;


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

	//other member fcns
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
fstream & operator>>(fstream & lhs, DietPlan & rhs);

//*******************************************************************

class DietPlanNode {
public:
	//constructors
	DietPlanNode();
	DietPlanNode(DietPlan newPlan, DietPlanNode * newNext = nullptr);

	//accessors, mutators
	DietPlan const & getPlan(void) const { return plan; }
	DietPlanNode * getNext(void) const { return pNext; }
	void setPlan(DietPlan const & newPlan) { plan = newPlan; }
	void setNext(DietPlanNode * const & newNext) { pNext = newNext; }

private:
	DietPlan plan;
	DietPlanNode * pNext;
};

//*******************************************************************

class DietPlanList {
public:
	//constructors, destructors
	DietPlanList();
	~DietPlanList();
	DietPlanList(DietPlanList const & original);
	DietPlanList & operator=(DietPlanList const & original);

	//member fcns
	//takes newPlan, creates a DietPlanNode using its data
	//appends it to the list, and updates the tail pointer
	void append(DietPlan const & newPlan);

	//clears the contents of an entire list, freeing memory
	void clear();
	//returns 1 if list is empty, 0 else
	int isEmpty();
	
	//searches list sequentially for first node whose plan's name variable
	//matches nameQuery exactly, and returns the pointer to that node
	//returns nullptr if nameQuery was not found
	DietPlanNode * search(string nameQuery);
	
private:
	//marks first and last elements of list
	//both nullptr if list is empty
	DietPlanNode * pHead;
	DietPlanNode * pTail;

	//removes the first DietPlanNode in the list
	//does nothing if list is already empty
	void deleteAtFront();
};