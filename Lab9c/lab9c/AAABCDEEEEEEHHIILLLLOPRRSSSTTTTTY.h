//header file for Lab 9c - Sorting

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

//prints out the elements of int array target of size target_size
//in the form { 1 2 3 ... }
void print_int_array(int target[], int target_size);

//sorts target int array of size target_size
//using insertion sort algorithm
void insertion_sort(int target[], int target_size);

//sorts target int array of size target_size
//using bubble sort algorithm
void bubble_sort(int target[], int target_size);

//exactly what it sounds like
void insertion_sort_driver(int target[], int target_size);

//what it sounds like, yo
void bubble_sort_driver(int target[], int target_size);