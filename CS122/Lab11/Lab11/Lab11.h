//header for Lab 11

#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::ostream;
using std::istream;
using std::string;

class Person {
public:
	Person(string newName = "Human Being", int newAge = 0, 
		char newGender = 'h', int newHeight = 0);
	Person(Person & orig);
	~Person() { }
	Person & operator=(Person & rhs);

	//setters
	void setName(string const newName) { name = newName; }
	void setAge(int const newAge) { age = newAge; }
	void setGender(char const newGender) { gender = newGender; }
	void setHeight(int const newHeight) { height = newHeight; }

	//getters
	string getName(void) const { return name; };
	int getAge(void) const { return age; };
	char getGender(void) const { return gender; }
	int getHeight(void) const { return height; }

	//prints out person characteristics, called by stream extraction operator
	void print(ostream & output);

protected:
	string name;
	int age;
	char gender;
	int height;
};

//reads in order name, age, gender, height
istream & operator>>(istream & lhs, Person & rhs);

//outputs in order name, age, gender, height
ostream & operator<<(ostream & lhs, Person & rhs);

class TestPerson : public Person {
public:
	TestPerson() { }
	void testConstructor(void);
	void testCopyConstructor(void);
	void testAssignmentOperator(void);

};

void testDriver(void);

typedef struct course {
	string courseName;
	int credits;
	//NOTE:
	//in Student class this represents student's grade in the course
	//in Teacher class this represents the average grade of all students
	//in the course being taught by the teacher.
	double grade;
} Course;

class Student : public Person {
public:
	//initializes a new student but gives them no courses
	Student(string newName, int newAge, char newGender, int newHeight);

	//getters
	int getNumCourses(void) const { return numCourses; }
	int getTotalCredits(void) const { return totalCredits; }
	//precondition: 0 <= i < numCourses
	Course getCourse(int i) const { return courseArray[i]; }

	//setters; never use
	void setNumCourses(int const newNumCourses) { numCourses = newNumCourses; }
	void setTotalCredits(int const newTotalCredits) {
		totalCredits = newTotalCredits;	}

	//other methods

	//adds a course to schedule
	//precondition: numCourses < 8
	void addCourse(string newCourseName, 
			int courseCredits, double newCurrentGrade);

	//clears entire schedule
	void clear(void);

	//computes GPA based on course array
	double computeGPA(void);

	//literally pointless in my implementation but the instructions
	//say to do it, so i guess this compute the total credits
	int computeCredits(void);

	//prints course load onto console, helper fcn for << operator
	void printCourses(ostream & output);

private:
	//holds the courses the student is taking this term
	Course courseArray[8];
	//number of courses taken this term
	int numCourses;
	//total credits taken this term
	int totalCredits;
};

//prints out list of student's courses and summary to the console
ostream & operator<<(ostream & lhs, Student & rhs);

class Teacher : public Student {
public:
	//initializes a new teacher but gives them no courses
	Teacher(string newName, int newAge, char newGender, int newHeight);

private:
	//holds the courses the teacher is teaching this term
	Course courseArray[8];
	//number of courses taught this term
	int numCourses;
	//total credits taught this term
	int totalCredits;
};

//prints out list of teacher's courses and summary to the console
ostream & operator<<(ostream & lhs, Teacher & rhs);