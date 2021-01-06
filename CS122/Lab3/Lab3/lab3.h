//header file for Lab 3

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <Windows.h>

typedef struct stackNode {
	double data;
	struct stackNode * pNext;
} StackNode;

//checks to see if stack is empty; returns true if so, false else
int isEmpty(StackNode * pStack);

//inserts a node with data of type double to top of stack
//node is allocated dynamically
//remember to pass in LOCATION of pStack when calling
void push(double value, StackNode ** pStack);

//deletes node from top (head) of stack
//remember to pass in LOCATION of pStack when calling
//WARNING!  stack cannot be empty when calling
void pop(StackNode ** pStack);

//returns value from top of stack
double peek(StackNode * pStack);

