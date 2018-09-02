//header for lab 9b

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

//debugger function
//prints out the contents of target int array of size target_size
void print_int_array(int target[], int target_size);

//binary search - searches target array of size array_size for my_value
//between left_index and right_index
//start with left_index at 0 and right_index at array_size - 1
//prec: target array is a sorted int array, myValue is a valid int
//post: gives message regarding whether target value was found
//returns array index location of target value
//or -1 if target value was not found
int bin_search(int target[], int my_value, int left_index, int right_index);