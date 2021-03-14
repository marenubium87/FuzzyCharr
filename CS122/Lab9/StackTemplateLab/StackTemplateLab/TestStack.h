#pragma once

#include "Stack.h"

template <class T>
class TestStack
{
public:
	TestStack();
	~TestStack();
	void Test(T &item1, T &item2);

private:
	Stack<T> theStack;
};

template <class T>
TestStack<T>::TestStack() : theStack(0) // this is initializing the newSize of the stack object to 0
{

}

template <class T>
TestStack<T>::~TestStack()
{

}

template <class T>
void TestStack<T>::Test(T &item1, T &item2)
{
	cout << "Is stack empty? " << theStack.isEmpty() << endl;
	cout << "Peek successful? " << theStack.peek(item2) << endl;
	if (theStack.peek(item2)) {
		cout << "Peek: " << item2 << endl;
	}
	cout << "Pop successful? " << theStack.pop(item2) << endl;
	cout << "Pushing " << item1 << " onto stack." << endl;
	theStack.push(item1);
	cout << "Is stack empty? " << theStack.isEmpty() << endl;
	cout << "Peek successful? " << theStack.peek(item2) << endl;
	theStack.peek(item2);
	if (theStack.peek(item2)) {
		cout << "Peek: " << item2 << endl;
	}
	item1 = 81;
	cout << "Pushing " << item1 << " onto stack." << endl;
	theStack.push(item1);
	cout << "Is stack empty? " << theStack.isEmpty() << endl;
	cout << "Peek successful? " << theStack.peek(item2) << endl;
	theStack.peek(item2);
	if (theStack.peek(item2)) {
		cout << "Peek: " << item2 << endl;
	}
	cout << "Pop successful? " << theStack.pop(item2) << endl;
	cout << "Pop: " << item2 << endl;
	cout << "Is stack empty? " << theStack.isEmpty() << endl;
	cout << "Peek successful? " << theStack.peek(item2) << endl;
	theStack.peek(item2);
	if (theStack.peek(item2)) {
		cout << "Peek: " << item2 << endl;
	}
	cout << "Pop successful? " << theStack.pop(item2) << endl;
	cout << "Pop: " << item2 << endl;
	cout << "Is stack empty? " << theStack.isEmpty() << endl;
	cout << "Peek successful? " << theStack.peek(item2) << endl;
	theStack.peek(item2);
	if (theStack.peek(item2)) {
		cout << "Peek: " << item2 << endl;
	}
	cout << "Pop successful? " << theStack.pop(item2) << endl;
}
