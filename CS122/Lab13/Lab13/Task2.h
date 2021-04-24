#pragma once

#include <iostream>

using std::cout;
using std::endl;
using std::cin;

class Mammal {
public:
	Mammal();
	virtual ~Mammal();

	virtual void Move() const;
	virtual void Speak() const;

protected:
	int age;
};

class Dog : public Mammal {
public:
	Dog();
	~Dog();

	void Move() const;
	void Speak() const;
};

class Cat : public Mammal {
public:
	Cat();
	~Cat();

	void Move() const;
	void Speak() const;
};

class Fox : public Mammal {
public:
	Fox();
	~Fox();

	void Move() const;
	void Speak() const;
};

class GuineaPig : public Mammal {
public:
	GuineaPig();
	~GuineaPig();

	void Move() const;
	void Speak() const;
};