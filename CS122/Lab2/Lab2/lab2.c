//source for lab 2

#include "lab2.h"

//allocates space on the heap for a new Node and initializes
//Node with information found in newData
//returns address of Node on the heap
Node * makeNode(Contact newData) {
	Node * pMem = (Node *)malloc(sizeof(Node));
	pMem->pNext = NULL;
	pMem->data = newData;
	return pMem;
}

//prints all contact information in the list to the console
void printList(Node * pList) {
	while (pList != NULL) {
		printf("--\n%s\n%s\n%s\n%s\n**\n\n",
			pList->data.name,
			pList->data.phone,
			pList->data.email,
			pList->data.title
		);
		pList = pList->pNext;
	}
	printf("End of list.\n\n");
}

//remember to pass in the *location* of pHead (e.g. &pHead)
int insertContactInOrder(Node **pHead, Contact newData) {

	Node * pMem = makeNode(newData);
	if (pMem == NULL) {
		return FALSE;
	}

	//if list is empty, or is inserting at front
	//is name field of newData less than name field of first element in list?
	if (*pHead == NULL || strcmp(newData.name, (*pHead)->data.name) < 0) {
		pMem->pNext = *pHead;
		*pHead = pMem;
	}
	else {
		Node * pCurr = *pHead;
		Node * pNext = pCurr->pNext;
		//move pCurr and pNext until the element to be inserted
		//should be between the two
		while (pNext != NULL && strcmp(newData.name, pNext->data.name) > 0) {
			pNext = pNext->pNext;
			pCurr = pCurr->pNext;
		}
		//perform insertion
		pMem->pNext = pNext;
		pCurr->pNext = pMem;
	}

	return TRUE;
}

//deletes a contact in the list based on the name field
//deletes the first occurrence of the name
int deleteContact(Node **pHead, Contact searchContact) {
	//is the list empty?
	if (*pHead == NULL) {
		return FALSE;
	}
	
	Node * pCurr = *pHead;
	//is the node we need to delete the first entry?
	if (strcmp(pCurr->data.name, searchContact.name) == 0){
		*pHead = pCurr->pNext;
		free(pCurr);
		return TRUE;
	}
	//look through the rest of the list
	else {
		Node * pPrev = NULL;
		while (pCurr != NULL &&
			strcmp(pCurr->data.name, searchContact.name) != 0) {

			//increment through list as long as there's no match and
			//we're not at the end
			pPrev = pCurr;
			pCurr = pCurr->pNext;
		}

		//if we stopped before pCurr became NULL, that means we found a match
		if (pCurr != NULL) {
			//link previous element to pCurr's link
			pPrev->pNext = pCurr->pNext;
			//we don't memory leak in this household
			free(pCurr);
			return TRUE;
		}
	}
	//if code execution makes it to here, didn't find a match in list
	return FALSE;
}

//loads all contact information from the given (and opened) infile,
//in alphabetic order, based on the name, into the list
//returns TRUE if all contacts were loaded; FALSE otherwise
int loadContacts(FILE * infile, Node ** pList) {
	
	//number of contacts loaded
	int i = 0;

	char nextLine[50] = "";

	//is there still contact info to grab?
	while (fgets(nextLine, 49, infile) != NULL) {
		
		//is nextLine just the new line character?  
		//if not, this is the start of a new contact
		if (strcmp(nextLine, "\n") != 0) {
			Contact tempContact = { { "" },{ "" },{ "" },{ "" } };
			//truncate the newline character
			nextLine[strlen(nextLine) - 1] = '\0';
			strcpy(tempContact.name, nextLine);
			fgets(nextLine, 49, infile);
			nextLine[strlen(nextLine) - 1] = '\0';
			strcpy(tempContact.phone, nextLine);
			fgets(nextLine, 49, infile);
			nextLine[strlen(nextLine) - 1] = '\0';
			strcpy(tempContact.email, nextLine);
			fgets(nextLine, 49, infile);
			nextLine[strlen(nextLine) - 1] = '\0';
			strcpy(tempContact.title, nextLine);
			
			//add contact to the list
			insertContactInOrder(pList, tempContact);
			i++;
		}
	}
	if (i > 0) {
		return TRUE;
	}
	else {
		return FALSE;
	}
}

//menu options for lab
void printMenu(void) {
	printf("Choose from the following options:\n\n");
	printf("  1.  About Address Book (TM)\n");
	printf("  2.  Add a contact\n");
	printf("  3.  Delete a contact\n");
	printf("  4.  List all contacts\n");
	printf("  5.  Load contacts from file\n");
	printf("  6.  Run unit tests\n");
	printf("  7.  Quit\n\n");
}

//the about section
void printAbout(void) {
	printf("Address Book (TM), copyright 2385\n\n");
	printf("Address Book (TM) is a product of the\n");
	printf("Nefarious Kitty Consortium (TM) and no\n");
	printf("part of this product may be fucked with\n");
	printf("or violent mauling may occur.  Enjoy!\n\n");
}

//wrapper to insert a contact
void insertContactWrapper(Node **pHead) {
	
	char tempCharr = '\0';
	scanf("%c", &tempCharr);

	char name[50];
	char phone[12]; //18005551234
	char email[50];
	char title[20];

	//acquire user input
	printf("Sigh, let's go through this song and dance...\n");
	printf("\nEnter the dude's name:  ");
	fgets(name, 49, stdin);
	printf("\nEnter the dude's digits, yo:  ");
	fgets(phone, 11, stdin);
	printf("\nWhat's their e-mail?  ");
	fgets(email, 49, stdin);
	printf("\nWhat should their titties be?  ");
	fgets(title, 19, stdin);

	//prune newline characters
	name[strlen(name) - 1] = '\0';
	phone[strlen(phone) - 1] = '\0';
	email[strlen(email) - 1] = '\0';
	title[strlen(title) - 1] = '\0';

	//place into temp contact
	Contact tempContact = { {""}, {""}, {""}, {""} };
	strcpy(tempContact.name, name);
	strcpy(tempContact.email, email);
	strcpy(tempContact.phone, phone);
	strcpy(tempContact.title, title);

	//perform insertion
	insertContactInOrder(pHead, tempContact);
	printf("\n\n\nAll done.  Now leave me alone.\n\n");
}

//wrapper to delete a contact
void deleteContactWrapper(Node **pHead) {
	printf("Excellent, excellent... *steeples fingers*\n");
	printf("Tell me the name of the offending individual and\n");
	printf("I will have them... removed.\n\n");
	
	//get user input
	char tempCharr = '\0';
	scanf("%c", &tempCharr);
	char name[50] = "";
	fgets(name, 49, stdin);

	//prune newline character from name
	name[strlen(name) - 1] = '\0';
	//place into temp contact
	Contact tempContact = { {""}, {""}, {""}, {""} };
	strcpy(tempContact.name, name);

	//search for deletion
	if (deleteContact(pHead, tempContact)) {
		printf("It has been done.  Go away now.\n\n");
	}
	else {
		printf("I couldn't find that individual.\n\n");
	}
}