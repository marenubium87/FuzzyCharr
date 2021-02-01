//source for exercise plan class

#include "ExercisePlan.h"

//*******************************************************************

//ExercisePlan Class
//constructors for ExercisePlan
ExercisePlan::ExercisePlan() {
	name = "";
	goal = 0;
	date = "";
}

ExercisePlan::ExercisePlan(string newName, int newGoal, string newDate) {
	name = newName;
	goal = newGoal;
	date = newDate;
}
ExercisePlan::ExercisePlan(ExercisePlan const & original) {
	*this = original;
}

ExercisePlan & ExercisePlan::operator=(ExercisePlan const & rhs) {
	name = rhs.name;
	goal = rhs.goal;
	date = rhs.date;
	return *this;
}

//others
//prompts user for new goal, changes goal accordingly, displays to screen
void ExercisePlan::editGoal(void) {
	int input = 0;
	cout << "Type in a new goal number of steps:  ";
	cin >> input;
	goal = input;
	cout << "Your new plan:" << endl << endl << *this;
}

//stream insertion operator, writing to console
ostream & operator<<(ostream & lhs, ExercisePlan const & rhs) {
	lhs << rhs.getName() << endl << rhs.getGoal() << endl << rhs.getDate();
	return lhs;
}

//stream insertion operator, writing to file
ofstream & operator<<(ofstream & lhs, ExercisePlan const & rhs) {
	lhs << rhs.getName() << endl << rhs.getGoal() << endl << rhs.getDate();
	lhs << endl << endl;
	return lhs;
}

//stream extraction operator, from file
fstream & operator>>(fstream & lhs, ExercisePlan & rhs) {
	string tempStr = "";
	int tempInt = 0;

	//gets the next line that isn't empty
	do {
		getline(lhs, tempStr);
	} while (tempStr == "" && !lhs.eof());

	//if we hit eof here return and give an error message
	if (lhs.eof()) {
		cout << "Error: unexpected end-of-file when reading from file" << endl;
		cout << "Exercise plan(s) may not have been read successfully!";
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

//ExercisePlanNode class
//default constructor
ExercisePlanNode::ExercisePlanNode() {
	plan.setName("");
	plan.setGoal(0);
	plan.setDate("");
	pNext = nullptr;
}

//constructor with args
ExercisePlanNode::ExercisePlanNode(ExercisePlan newPlan, 
		ExercisePlanNode * newNext) {
	plan = newPlan;
	pNext = newNext;
}

//returns the plan's name in the current ExercisePlanNode
string const ExercisePlanNode::getPlanName() {
	return plan.getName();
}

//allows access to the editGoal fcn in DietPlan from this interface
void ExercisePlanNode::editPlanGoal() {
	plan.editGoal();
}

//*******************************************************************
//ExercisePlanList class

//default constructor
ExercisePlanList::ExercisePlanList() {
	pHead = nullptr;
	pTail = nullptr;
}

//destructor
ExercisePlanList::~ExercisePlanList() {
	clear();
}

//copy constructor
ExercisePlanList::ExercisePlanList(ExercisePlanList const & original) {
	*this = original;
}

//assignment operator
ExercisePlanList & ExercisePlanList::operator=
		(ExercisePlanList const & original) {
	//clears current list to avoid leaking memory
	clear();
	ExercisePlanNode * pCurrRHS = original.pHead;
	while (pCurrRHS != nullptr) {
		append(pCurrRHS->getPlan());
		pCurrRHS = pCurrRHS->getNext();
	}
	return *this;
}

//takes newPlan, creates a ExercisePlanNode using its data
//appends it to the list, and updates the tail pointer
void ExercisePlanList::append(ExercisePlan const & newPlan) {
	//creates new node
	ExercisePlanNode * pTemp = new ExercisePlanNode(newPlan);
	//is list currently empty?
	if (pHead == nullptr) {
		pHead = pTemp;
		pTail = pTemp;
	}
	else {
		pTail->setNext(pTemp);
		pTail = pTemp;
	}
}

//removes the first ExercisePlanNode in the list
//does nothing if list is already empty
void ExercisePlanList::deleteAtFront() {
	//is list empty?
	if (pHead == nullptr) {
		return;
	}
	ExercisePlanNode * pTemp = pHead;
	pHead = pHead->getNext();
	//did we just delete the last element in the list?  if so, reset tail ptr
	if (pHead == nullptr) {
		pTail = nullptr;
	}
	//free memory
	delete pTemp;
}

//returns 1 if list is empty, 0 else
int ExercisePlanList::isEmpty() {
	if (pHead == nullptr) {
		return 1;
	}
	else {
		return 0;
	}
}

//clears the contents of an entire list, freeing memory
void ExercisePlanList::clear() {
	while (pHead != nullptr) {
		deleteAtFront();
	}
}

//prints out the contents of the list to the console
void ExercisePlanList::print() const {
	cout << "Your diet plan for the week of " <<
		pHead->getPlan().getDate() << ":" << endl << endl;
	ExercisePlanNode * pCurr = pHead;
	while (pCurr != nullptr) {
		cout << pCurr->getPlan() << endl << endl;
		pCurr = pCurr->getNext();
	}
	cout << "End of plan *** ";
}

//stores the contents of the list to file
void ExercisePlanList::store(fstream & outputFile) const {
	ExercisePlanNode * pCurr = pHead;
	while (pCurr != nullptr) {
		outputFile << pCurr->getPlan() << endl << endl;
		pCurr = pCurr->getNext();
	}
}

//searches list sequentially for first node whose plan's name
//(day of the week) matches nameQuery exactly, 
//and allows the user to modify the goal steps for that day
void ExercisePlanList::search(string const & nameQuery) {
	ExercisePlanNode * pCurr = pHead;
	while (pCurr != nullptr) {
		if (pCurr->getPlanName() == nameQuery) {
			pCurr->editPlanGoal();
			return;
		}
		pCurr = pCurr->getNext();
	}

	//if code makes it to here nameQuery was not found in list
	cout << "Could not find a plan with name '" << nameQuery << "' "
		<< "in list.";
}
