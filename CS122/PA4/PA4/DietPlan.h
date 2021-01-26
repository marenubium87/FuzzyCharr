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
	DietPlanNode(DietPlan newPlan, DietPlanNode * pNext = nullptr);

	//accessors, mutators
	const DietPlan & getPlan(void) const { return plan; }
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

	//accessors, mutators
	DietPlanNode * getTail() const { return pTail; }
	void setHead(DietPlanNode * const newHead) { pHead = newHead; }
	void setTail(DietPlanNode * const newTail) { pTail = newTail; }

	//member fcns
	void append(DietPlanNode newNode);
	void deleteAtFront();
	int isEmpty();
	int clear();
	DietPlanNode * search(string nameQuery);

private:
	DietPlanNode * pHead;
	DietPlanNode * pTail;
};