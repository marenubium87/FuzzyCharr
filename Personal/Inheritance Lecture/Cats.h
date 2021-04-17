#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::string;
using std::endl;

class Cat {
public:
	Cat() : name("Fluffy"), age(3), magicPowers("telekinesis") {
		//name = "Fluffy";
		//age = 3;
		//magicPowers = "telekinesis";
	}
	Cat(string newName, int newAge, string newMagicPowers) {
		name = newName;
		age = newAge;
		magicPowers = newMagicPowers;
	}
	~Cat() { cout << "Cat destructor" << endl; }
	string name;

protected:
	int age;
	
private:
	string magicPowers;
};

class Lynx : private Cat {
public:
	Lynx() : Cat("Shadow", 4, "Shadows of the Abyss") {
		tufts = "lots";
		family = "Lynx";
		floof = "very lots";
	}
	Lynx(string newName, int newAge, string newMagicPowers) : Cat(newName, newAge, newMagicPowers) {
		tufts = "lots";
		family = "Lynx";
		floof = "very lots";
	}
	~Lynx() { cout << "Lynx destructor" << endl; }
	string tufts;

protected:
	string family;

private:
	string floof;
};

class EurasianLynx : private Lynx {
public:
	EurasianLynx() {
		furColor = "silver";
		diet = "bunbuns";
		favoriteFood = "birds";
	}
	~EurasianLynx() { cout << "EurasianLynx destructor" << endl; }
	string furColor;

protected:
	string diet;

private:
	string favoriteFood;
};