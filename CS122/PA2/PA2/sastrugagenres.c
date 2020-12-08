//source file for functions to deal with genres


#include "sastrugaGenres.h"

//allocates space on the heap for a new GenreNode and initializes
//with information found in targetGenre
//returns address of GenreNode on the heap
GenreNode * makeGenre(char * targetGenre) {
	GenreNode * pMem = (GenreNode *)malloc(sizeof(GenreNode));
	strcpy(pMem->genre, targetGenre);
	pMem->pNext = NULL;
	return pMem;
}

//inserts genreNode contaniing targetGenre in front of genre list
//remember to pass in the *location* of pHead when calling
void insertGenreAtFront(GenreNode ** pGenreList, char * targetGenre) {
	GenreNode * pMem = makeGenre(targetGenre);
	pMem->pNext = *pGenreList;
	*pGenreList = pMem;
}

//deletes node containing targetGenre, if found from the list
//returns true if fcn found a match and deleted, false if it didn't
//remember to pass in the *location* of pHead when calling
int deleteGenre(GenreNode ** pList, char * targetGenre) {
	//we only do this if list isn't empty
	if (*pList != NULL) {
		//move pCurr through the list
		GenreNode * pCurr = *pList;
		
		//is the node we need to delete the first entry?
		if (strcmp(pCurr->genre, targetGenre) == 0) {
			*pList = pCurr->pNext;
			free(pCurr);
			return TRUE;
		}
		else {
			GenreNode * pPrev = NULL;
			//increment through until we reach end of list or find target
			while (pCurr != NULL && strcmp(pCurr->genre, targetGenre) != 0) {
				pPrev = pCurr;
				pCurr = pCurr->pNext;
			}
			//if pCurr isn't NULL, means we found a match, so delete entry
			if (pCurr != NULL) {
				pPrev->pNext = pCurr->pNext;
				free(pCurr);
				return TRUE;
			}
		}
	}
	//if code makes it to here, nothing was deleted
	return FALSE;
}

//lists out all contents of genre linked list to console
void printGenreList(GenreNode * pHead) {
	GenreNode * pCurr = pHead;
	if (pCurr == NULL) {
		printf("N/A");
	}
	else {
		while (pCurr->pNext != NULL) {
			printf("%s | ", pCurr->genre);
			pCurr = pCurr->pNext;
		}
		printf("%s", pCurr->genre);
	}
}