//header for lab 2

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <Windows.h>

typedef struct contact {
	char name[50];
	char phone[12]; //18005551234
	char email[50];
	char title[20];
} Contact;

typedef struct node
{
	Contact data;
	struct node * pNext;
} Node;

//allocates space on the heap for a new Node and initializes
//Node with information found in newData
//returns address of Node on the heap
Node * makeNode(Contact newData);

//prints all contact information in the list to the console
void printList(Node * pList);

//places newData into the correct (sorted) position into list
//remember to pass in the *location* of pHead (e.g. &pHead)
int insertContactInOrder(Node **pHead, Contact newData);

//deletes a contact in the list based on the name field
//deletes the frist occurrence of the name
int deleteContact(Node **pHead, Contact searchContact);

//loads all contact information from the given (and opened) infile,
//in alphabetic order, based on the name, into the list
//returns TRUE if all contacts were loaded; FALSE otherwise
int loadContacts(FILE * infile, Node ** pList);

//menu options for lab
void printMenu(void);

//the about section
void printAbout(void);

//wrapper to insert a contact
void insertContactWrapper(Node **pHead);

//wrapper to delete a contact
void deleteContactWrapper(Node **pHead);