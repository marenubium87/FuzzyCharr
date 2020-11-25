//source file for list testing functions

#include "lab2.h"
#include "testList.h"

Contact testContact1 = {
	{ "Isee Weiner" },
	{ "18005553875" },
	{ "richardshaft@pecker.com" },
	{ "Wang Wrangler" }
};

Contact testContact2 = {
	{ "Bob Dole" },
	{ "18005551234" },
	{ "pineappledood@something.com" },
	{ "Fruit Congressman" }
};

Contact testContact3 = {
	{ "Spherical Blob" },
	{ "18005554812" },
	{ "ballborbblorb@round.com" },
	{ "Glorp Glorp" }
};

Contact testContact4 = {
	{ "Iama Moo" },
	{ "18005552273" },
	{ "floofymoo@beefsteak.net" },
	{ "Cattle King" }
};

Contact testSearchContact1 = {
	{ "Isee Weiner" },
	{ "" },
	{ "" },
	{ "" }
};

Contact testSearchContact2 = {
	{ "Bob Dole" },
	{ "" },
	{ "" },
	{ "" }
};

Contact testSearchContact3 = {
	{ "Spherical Blob" },
	{ "" },
	{ "" },
	{ "" }
};

Contact testSearchContact4 = {
	{ "Iama Moo" },
	{ "" },
	{ "" },
	{ "" }
};

Contact testSearchContact5 = {
	{ "Nonexistent Name" },
	{ "" },
	{ "" },
	{ "" }
};

//aux function for testing
//returns 1 if all fields in both contacts match, 0 if not
//returns -1 if something went wrong
int doContactsMatch(Contact firstContact, Contact secondContact) {
	int i[4] = { -2, -2, -2, -2 };
	i[0] = strcmp(firstContact.name, secondContact.name);
	i[1] = strcmp(firstContact.phone, secondContact.phone);
	i[2] = strcmp(firstContact.email, secondContact.email);
	i[3] = strcmp(firstContact.title, secondContact.title);
	for (int j = 0; j < 4; j++) {
		if (i[j] != 0) {
			if (i[j] == -2) {
				return -1;
			}
			else {
				return 0;
			}
		}
		j++;
	}
	return 1;
}

//wrapper to incorporate all tests
void testWrapper(void) {
	printf("Performing unit tests...\n\n");
	Node * pHead = NULL;
	FILE * infile = fopen("testinput.dat", "r");
	testInsertContactInOrder(&pHead);
	testDeleteContact(&pHead);
	testLoadContacts(&pHead, infile);
}

//test fcn for insert contact in order
void testInsertContactInOrder(Node ** pHead) {
	printf("Testing insertion in order...  ");
	
	//insert into empty list
	insertContactInOrder(pHead, testContact1);
	//insert at front
	insertContactInOrder(pHead, testContact2);
	//insert at end
	insertContactInOrder(pHead, testContact3);
	//insert in middle
	insertContactInOrder(pHead, testContact4);
	
	//check state of list
	int i = 0;
	Node * pCurr = *pHead;
	i += doContactsMatch(pCurr->data, testContact2);
	pCurr = pCurr->pNext;
	i += doContactsMatch(pCurr->data, testContact4);
	pCurr = pCurr->pNext;
	i += doContactsMatch(pCurr->data, testContact1);
	pCurr = pCurr->pNext;
	i += doContactsMatch(pCurr->data, testContact3);
	pCurr = pCurr->pNext;

	if (pCurr == NULL && i == 4) {
		printf("TEST PASSED\n\n");
	}
	else {
		printf("TEST FAILED\n\n");
	}
}

//test fcn for delete contact
void testDeleteContact(Node ** pHead) {
	printf("Testing deletions...  ");
	int expectedValues[7] = { 1, 1, 1, 0, 1, 0, 1 };
	int actualValues[7] = { -1, -1, -1, -1, -1, -1, -1 };

	//delete from middle expect 1
	actualValues[0] = deleteContact(pHead, testSearchContact4);
	//delete from end expect 1
	actualValues[1] = deleteContact(pHead, testSearchContact3);
	//delete from beginning expect 1
	actualValues[2] = deleteContact(pHead, testSearchContact2);
	//delete element with no match expect 0
	actualValues[3] = deleteContact(pHead, testSearchContact5);
	//delete last element expect 1
	actualValues[4] = deleteContact(pHead, testSearchContact1);
	//delete from empty list expect 0
	actualValues[5] = deleteContact(pHead, testSearchContact1);
	//final configuration of list expect 1
	actualValues[6] = (*pHead == NULL) ? 1 : 0;

	for (int i = 0; i < 7; i++) {
		if (expectedValues[i] != actualValues[i]) {
			printf("TEST FAILED\n\n");
			return;
		}
	}
	printf("TEST PASSED\n\n");
}

//test fcn for loading contacts from infile
void testLoadContacts(Node ** pHead, FILE * infile) {
	
	printf("Testing loading contacts from infile...  ");
	loadContacts(infile, pHead);
	
	//check if proper loading
	int i = 0;
	Node * pCurr = *pHead;
	i += doContactsMatch(testContact2, pCurr->data);
	pCurr = pCurr->pNext;
	i += doContactsMatch(testContact1, pCurr->data);
	pCurr = pCurr->pNext;
	i += doContactsMatch(testContact3, pCurr->data);
	pCurr = pCurr->pNext;
	if (i == 3 && pCurr == NULL) {
		printf("TEST PASSED\n\n");
	}
	else {
		printf("TEST FAILED\n\n");
	}
	
	//clean up
	deleteContact(pHead, testContact3);
	deleteContact(pHead, testContact1);
	deleteContact(pHead, testContact2);
}