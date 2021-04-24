#include "Task2.h"

Mammal::Mammal(void) : age(1) {
	cout << "Mammal constructor." << endl;
}

Mammal::~Mammal(void) {
	cout << "Mammal destructor." << endl;
}

void Mammal::Move() const {
	cout << "Mammal moves." << endl;
}

void Mammal::Speak() const {
	cout << "Mammal speaks." << endl;
}

Dog::Dog(void) {
	cout << "Constructing Spot." << endl;
}

Dog::~Dog(void) {
	cout << "Bye, Spot." << endl;
}

void Dog::Move() const {
	cout << "Spot moves!" << endl;
}

void Dog::Speak() const {
	cout << "Ruff ruff." << endl;
}

Cat::Cat(void) {
	cout << "Mrow has entered the chat." << endl;
}

Cat::~Cat(void) {
	cout << "Mrow has left the chat." << endl;
}

void Cat::Move() const {
	cout << "Slinking about, hunting birbs." << endl;
}

void Cat::Speak() const {
	cout << "*probably contented purring*" << endl;
}

Fox::Fox(void) {
	cout << "Floofy fox appears!" << endl;
}

Fox::~Fox(void) {
	cout << "Floofy fox disappears!" << endl;
}

void Fox::Move() const {
	cout << "Snuggly fox moves about." << endl;
}

void Fox::Speak() const {
	cout << "Fox makes... fox noises." << endl;
}

GuineaPig::GuineaPig(void) {
	cout << "Dumpling has arrived." << endl;
}

GuineaPig::~GuineaPig(void) {
	cout << "Dumpling goes elsewhere." << endl;
}

void GuineaPig::Move() const {
	cout << "Guinea pig waddles about, probably." << endl;
}

void GuineaPig::Speak() const {
	cout << "*oinks, but probably in guinea*" << endl;
}