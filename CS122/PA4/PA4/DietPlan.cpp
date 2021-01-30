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
	plan.setName("");
	plan.setGoal(0);
	plan.setDate("");
	pNext = nullptr;
}

//constructor with args
DietPlanNode::DietPlanNode(DietPlan newPlan, DietPlanNode * newNext) {
	plan = newPlan;
	pNext = newNext;
}

//*******************************************************************
//DietPlanList class

//default constructor
DietPlanList::DietPlanList() {
	pHead = nullptr;
	pTail = nullptr;
}

//destructor
DietPlanList::~DietPlanList() {
	clear();
}

//copy constructor
DietPlanList::DietPlanList(DietPlanList const & original) {
	*this = original;
}

//assignment operator
DietPlanList & DietPlanList::operator=(DietPlanList const & original) {
	//clears current list to avoid leaking memory
	clear();
	DietPlanNode * pCurrRHS = original.pHead;
	while (pCurrRHS != nullptr) {
		append(pCurrRHS->getPlan());
		pCurrRHS = pCurrRHS->getNext();
	}
	return *this;
}

//takes newPlan, creates a DietPlanNode using its data
//appends it to the list, and updates the tail pointer
void DietPlanList::append(DietPlan const & newPlan) {
	//creates new node
	DietPlanNode * pTemp = new DietPlanNode(newPlan);
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

//removes the first DietPlanNode in the list
//does nothing if list is already empty
void DietPlanList::deleteAtFront() {
	//is list empty?
	if (pHead == nullptr) {
		return;
	}
	DietPlanNode * pTemp = pHead;
	pHead = pHead->getNext();
	//did we just delete the last element in the list?  if so, reset tail ptr
	if (pHead == nullptr) {
		pTail = nullptr;
	}
	//free memory
	delete pTemp;
}

//returns 1 if list is empty, 0 else
int DietPlanList::isEmpty() {
	if (pHead == nullptr) {
		return 1;
	}
	else {
		return 0;
	}
}

//clears the contents of an entire list, freeing memory
void DietPlanList::clear() {
	while (pHead != nullptr) {
		deleteAtFront();
	}
}

//searches list sequentially for first node whose plan's name variable
//matches nameQuery exactly, and returns the pointer to that node
//returns nullptr if nameQuery was not found
DietPlanNode * DietPlanList::search(string const nameQuery) {
	
	DietPlanNode * pSearch = this->pHead;

	while (pSearch != nullptr) {
		if (nameQuery == pSearch->getPlan().getName()) {
			return pSearch;
		}
		pSearch = pSearch->getNext();
	}

	//traversed through list, didn't find result, pSearch now nullptr
	return pSearch;
}