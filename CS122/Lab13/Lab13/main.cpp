#include "Task1.h"
#include "Task2.h"

int main(void) {

	//Mammal * pDawg = new Dog;
	//pDawg->Move();
	//pDawg->Speak();
	//delete pDawg;

	//Mammal * pDawg2 = new Dog;
	//pDawg2->Mammal::Move();
	//pDawg2->Move();
	//pDawg2->Speak();
	//delete pDawg2;

	Mammal * myMammal = new Dog;



	Mammal * mammalArray[5];
	Mammal * ptr;

	int choice, i;
	for (i = 0; i < 5; i++) {
		cout << "(1) dog  (2)  cat  (3)  fox  (4)  guinea pig:  ";
		cin >> choice;

		switch (choice) {
		case 1:  ptr = new Dog;
			break;
		case 2:  ptr = new Cat;
			break;
		case 3:  ptr = new Fox;
			break;
		case 4:  ptr = new GuineaPig;
			break;
		default:  ptr = new Mammal;
			break;
		}
		mammalArray[i] = ptr;
	}

	for (i = 0; i < 5; i++) {
		mammalArray[i]->Speak();
	}

	return 0;
}