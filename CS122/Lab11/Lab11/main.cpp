//Lab 11
//13 Apr 2021

#include "Lab11.h"

int main() {
	testDriver();

	Student Max("Max Kitty", 5, 'M', 36);
	Max.addCourse("MEOW203 Intermediate Kitty Things", 3, 3.7);


	cout << endl << endl << Max;
	cout << "Max's GPA is " << Max.computeGPA();

	Teacher Floofy("Floofy", 13, 'F', 33);
	
	Floofy.addCourse("HUNT225 Intro to Birb Hunting", 3, 3.9);
	Floofy.addCourse("FLOF301 Advanced Floofiness 1", 4, 4.0);
	Floofy.addCourse("PURR231 Vocalization 2", 3, 3.5);
	Floofy.addCourse("NAPP353 Napping Location Optimization", 3, 3.7);
	Floofy.addCourse("FLOF302 Advanced Floofiness 2", 4, 3.8);
	Floofy.addCourse("MEOW210 Annoying Hoomans 1", 4, 3.7);
	Floofy.addCourse("NAPP251 Intermediate Lounging", 3, 4.0);
	cout << endl << endl << Floofy;

	cout << endl << endl;

	int choice = 0;
	string tempStr = "";
	while (choice != 3) {
		cout << "Hello student: " <<
			"Max Kitty$70*#&2031ff#error:database corrup#*(^!eofbit(#"<< endl
		<< "1 to add a course, 2 to view your courses, 3 to quit:  ";
		cin >> choice;
		std::cin.ignore();

		if (choice == 1) {
			cout << endl
				<< "Your instructor has the following courses available."
				<< endl << "Type the course id to add a course." 
				<< endl << endl;
			Floofy.printCourses(cout);
			cout << endl;
			std::getline(cin, tempStr);

			int i = 0;
			while (tempStr.compare(0, 7, Floofy.getCourse(i).courseName, 0, 7)
				!= 0) {
				i++;
			}
			Max.addCourse(Floofy.getCourse(i).courseName,
				Floofy.getCourse(i).credits,
				Floofy.getCourse(i).grade);
			cout << "Your course has been added." << endl << endl;
		}
		else if (choice == 2) {
			cout << endl << "Your current courses:" << endl << endl;
			Max.printCourses(cout);
		}
	}

	cout << "Okay, bai236969ff#0cout << \'warning data corrup221*((" << endl;

	return 0;
}