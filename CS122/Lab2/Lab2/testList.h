//header file for list testing functions

//aux function for testing
//returns 1 if all fields in both contacts match, 0 if not
//returns -1 if something went wrong
int doContactsMatch(Contact firstContact, Contact secondContact);

//wrapper to incorporate all tests
void testWrapper(void);

//test fcn for insert contact in order
void testInsertContactInOrder(Node ** pHead);

//test fcn for delete contact
void testDeleteContact(Node ** pHead);

//test fcn for loading contacts from infile
void testLoadContacts(Node ** pHead, FILE * infile);