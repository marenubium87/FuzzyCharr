//PA7 Simpletron
//17 Apr 2021

#include "PA7.h"

int main() {
	Simpletron<int> Bob;
	//simpletron1:  reads two numbers, computes and prints sum
	//simpletron2:  reads six positive numbers, computes and prints sum
	//simpletron3:  reads three numbers, computes and prints average
	//				counter controlled loop, first number read is counter, > 0
	//simpletron4:  reads series of numbers, determines and prints largest
	//				first number read indicates # of nums to be processed
	Bob.loadProgram("simpletron2.sml");
	Bob.executeProgram();


	return 0;
}