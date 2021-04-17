//source for Lab 11

#include "Lab11.h"

Person::Person(string newName, int newAge, char newGender, int newHeight) {
	name = newName;
	age = newAge;
	gender = newGender;
	height = newHeight;
}

Person::Person(Person & orig) {
	*this = orig;
}

Person & Person::operator=(Person & rhs) {
	name = rhs.name;
	age = rhs.age;
	gender = rhs.gender;
	height = rhs.height;

	return *this;
}

void Person::print(ostream & output) {
	output << getName() << endl
		<< "Age:  " << getAge() << endl
		<< "Gender:  " << getGender() << endl
		<< "Height:  " << getHeight() << " cm" << endl
		<< "***" << endl;
}

//reads in order name, age, gender, height
istream & operator>>(istream & lhs, Person & rhs) {
	string tempName = "";
	int tempAge = 0;
	char tempGender = '\0';
	int tempHeight = 0;
	lhs >> tempName >> tempAge >> tempGender >> tempHeight
		>> std::ws;

	rhs.setName(tempName);
	rhs.setAge(tempAge);
	rhs.setGender(tempGender);
	rhs.setHeight(tempHeight);

	return lhs;
}

//outputs in order name, age, gender, height
ostream & operator<<(ostream & lhs, Person & rhs) {
	rhs.print(lhs);
	return lhs;
}

//prec:  a test person was instantiated with no arguments
void TestPerson::testConstructor(void) {
	cout << "testing constructor... ";
	if (this->getName() == "Human Being" && this->getAge() == 0
			&& this->getGender() == 'h' && this->getHeight() == 0) {
		cout << "passed";
	}
	else {
		cout << "failed";
	}
	cout << endl;
}

//prec:  John's attributes have been set to 
//"Bob Dole", 999, 'M', 65
void TestPerson::testCopyConstructor(void) {
	cout << "testing copy constructor... ";
	if (this->getName() == "Bob Dole" && this->getAge() == 999
		&& this->getGender() == 'M' && this->getHeight() == 65) {
		cout << "passed";
	}
	else {
		cout << "failed";
	}
	cout << endl;
}

//prec://prec:  Bob's attributes have been set to 
//"Bob Dole", 999, 'M', 65
void TestPerson::testAssignmentOperator(void) {
	cout << "testing assignment operator... ";
	if (this->getName() == "Bob Dole" && this->getAge() == 999
		&& this->getGender() == 'M' && this->getHeight() == 65) {
		cout << "passed";
	}
	else {
		cout << "failed";
	}
	cout << endl;
}

void testDriver(void) {
	TestPerson John;
	John.testConstructor();
	John.setName("Bob Dole");
	John.setAge(999);
	John.setGender('M');
	John.setHeight(65);
	TestPerson Bob(John);
	Bob.testCopyConstructor();
	John = Bob;
	John.testAssignmentOperator();
}

//initializes a new student but gives them no courses
Student::Student(string newName, int newAge, char newGender, int newHeight) :
		Person(newName, newAge, newGender, newHeight) {
	
	numCourses = 0;
	totalCredits = 0;
}

//adds a course to student's schedule
//precondition: student has less than eight courses currently
void Student::addCourse(string newCourseName,
		int courseCredits, double newCurrentGrade) {
	
	courseArray[numCourses].courseName = newCourseName;
	courseArray[numCourses].credits = courseCredits;
	courseArray[numCourses].grade = newCurrentGrade;

	numCourses++;
	totalCredits += courseCredits;
}

//clears a student's entire schedule
void Student::clear(void) {
	numCourses = 0;
	totalCredits = 0;
}

//compute student's GPA based on their course 
//precondition: student must be taking more than zero courses
double Student::computeGPA(void) {
	double temp = 0.0;
	for (int i = 0; i < numCourses; i++) {
		temp += courseArray[i].grade;
	}
	return temp /= numCourses;
}

int Student::computeCredits(void) {
	int temp = 0;
	for (int i = 0; i < numCourses; i++) {
		temp += courseArray[i].credits;
	}
	return temp;
}

//prints course load onto console
void Student::printCourses(ostream & output) {
	for (int i = 0; i < getNumCourses(); i++) {
		output << getCourse(i).courseName << endl
			<< "Credits:  " << getCourse(i).credits << "\t"
			<< "Grade: " << getCourse(i).grade << endl << endl;
	}
}

//prints out list of student's courses and summary to the console
ostream & operator<<(ostream & lhs, Student & rhs) {
	lhs << "Student record: " << endl;
	rhs.Person::print(lhs);
	lhs << "Courses this term: " << endl << endl;
	rhs.printCourses(lhs);

	return lhs;
}

Teacher::Teacher(string newName, int newAge, char newGender, int newHeight) :
		Student(newName, newAge, newGender, newHeight) {

	numCourses = 0;
	totalCredits = 0;
}

//prints out list of teacher's courses and summary to the console
ostream & operator<<(ostream & lhs, Teacher & rhs) {
	lhs << "Teacher record: " << endl;
	rhs.Person::print(lhs);
	lhs << "Courses this term: " << endl << endl;
	rhs.printCourses(lhs);

	return lhs;
}
