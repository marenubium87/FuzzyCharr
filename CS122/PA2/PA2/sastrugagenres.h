//header file for functions to deal with genres

//genre structure (singly-linked list)
typedef struct genreNode {
	char genre[40];
	struct genreNode * pNext;
} GenreNode;

//allocates space on the heap for a new GenreNode and initializes
//with information found in newData
//returns address of GenreNode on the heap
GenreNode * makeGenre(char * newGenre);

//inserts genreNode contaniing newData to front of genre linked list
void insertGenreAtFront(GenreNode ** pList, char * newGenre);

//lists out all contents of genre linked list to console
void printGenreList(GenreNode * pHead);

//deletes node containing targetGenre, if found from the list
//returns true if fcn found a match and deleted, false if it didn't
//remember to pass in the *location* of pHead when calling
int deleteGenre(GenreNode ** pList, char * targetGenre);