//Aerie, CS121
//Instructor: Reynx <3
//Lab 13 Bit Operations
//19 Aug 2020

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>
#include <Windows.h>

//prints out num in binary format
//and the number of positive place values given
//(usually some multiple of 8 is ideal)
void printBin(int num, int places) {
	int spaceCounter = 0;
	printf("\nNumber is %d\n", num);
	printf("Binary representation:  ");
	for (int i = places - 1; i >= 0; i--) {
		if (num / (int) pow(2, i) == 1) {
			num -= pow(2, i);
			printf("1");
		}
		else {
			printf("0");
		}
		spaceCounter++;
		if (spaceCounter == 4) {
			spaceCounter = 0;
			Sleep(200);
			printf(" ");
		}
	}
	printf("\n");
}

//shifts an integer variable num 4 bits to the right and returns it
//also prints out the binary equivalents in the number of places desired
int shift4Right(int num, int places) {
	printBin(num, places);
	printf("\nShifting 4 places to the right...\n");
	num = num >> 4;
	printBin(num, places);
	return num;
}

//using bit shifting, calculates the operation
//num * 2 ^ pow and returns it
int power2(int num, int pow) {
	printBin(num, 32);
	printf("\nComputing %d * 2 ^ %d...\n", num, pow);
	num = num << pow;
	printBin(num, 32);
	return num;
}

//remember me?
void statusBar(int status) {
	for (int i = 0; i < 10; i++) {
		printf(". ");
		Sleep(250);
	}
	Sleep(400);
	if (status) {
		printf("done.\n");
	}
	else {
		printf("FAILED.\n");
	}
	Sleep(700);
}

//i need this function to make a joke, sorry
int stuffMeatProduct(int casing, char meat) {
	//allocate room
	casing = casing << 8;
	//stuff meats
	printf("\n\nNext character is %c.\n", meat);
	int meatASCII = meat;
	Sleep(750);
	printf("ASCII value is %d.\n\n", meatASCII);
	Sleep(750);
	printBin(meatASCII, 32);
	Sleep(1000);
	printf("\nStuffing into casing ");
	casing = casing | meat;
	statusBar(1);
	Sleep(750);
	return casing;
}

//does the thing indicated by task 3 lab 13
void task3Wrapper(void) {
	printf("Type four characters then press enter:  ");
	char meatProducts[4] = { '\0' };
	int sausageCasing = 0;
	for (int i = 0; i < 4; i++) {
		scanf(" %c", &meatProducts[i]);
	}
	for (int i = 0; i < 4; i++) {
		sausageCasing = 
			stuffMeatProduct(sausageCasing, meatProducts[i]);
	}
	printf("\n\n\nFinal value of sausage is: %d\n\n", sausageCasing);
	printBin(sausageCasing, 32);
}

int main() {
	printf("  LAB 13 STUFFS\n\n\n");
	printf(" ***Task 1\n\n");
	int num1 = 0;
	printf("Type an integer to shift:  ");
	scanf("%d", &num1);
	shift4Right(num1, 32);
	printf("\n\n");

	printf(" ***Task 2\n\n");
	int num2a = 0;
	int num2b = 0;
	printf("Type a number:  ");
	scanf("%d", &num2a);
	printf("\n\n");
	printf("Type an integer for the exponent:  ");
	scanf("%d", &num2b);
	printf("\n\n");
	power2(num2a, num2b);
	printf("\n\n");

	printf(" ***Task 3\n\n");
	task3Wrapper();
	printf("\n\n");
	system("pause");
	return 0;
}