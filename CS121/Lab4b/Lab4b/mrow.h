//header for Lab 4 Part 2

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

//bonus amounts
#define ALLSTAR 25000
#define REGULARMVP 75000
#define WORLDMVP 100000
#define GOLDGLOVE 50000
#define SILVERSLUG 35000
#define HOMERUNCHAMP 25000
#define BATTINGCHAMP 25000

//returns all-star bonus amount as int if user enters 'y'
int wasAllStar(void);

//returns regular season MVP bonus amount as int if user enters 'y'
int wasRegularMVP(void);

//returns world series MVP bonus amount as int if user enters 'y'
int wasWorldMVP(void);

//returns gold glove bonus amount as int if user enters 'y'
int wasGoldGlove(void);

//returns silver slugger award bonus amount as int if user enters 'y'
int wasSilverSlug(void);

//returns home run champ bonus amount as int if user enters 'y'
int wasHomeRunChamp(void);

//returns batting average champ bonus amount as int if user enters 'y'
int wasBattingChamp(void);