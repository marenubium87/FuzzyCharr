//source file for Lab 9c - Sorting

#include "AAABCDEEEEEEHHIILLLLOPRRSSSTTTTTY.h"

//prints out the elements of int array target of size target_size
//in the form { 1 2 3 ... }
void print_int_array(int target[], int target_size)
{
	printf("\nTarget array composition is\n{");
	for (int i = 0; i < target_size; i++)
	{
		printf("%d ", target[i]);
	}
	printf("}\n\n");
}

//sorts target int array of size target_size
//using insertion sort algorithm
void insertion_sort(int target[], int target_size)
{
	//catches people trying to fuck with me
	if (target_size <= 1)
	{
		printf("Nope.  Aborting.\n");
		return;
	}

	int swapContainer = 0;

	//partition index holds the index of the first element in the -nonsorted- region
	//that is, partition index points to the location of the first -unsorted- element
	int partitionIndex = 1;
	while (partitionIndex < target_size)
	{
		for (int i = partitionIndex; i > 0; i--)
		{
			//check location i with the element to its left... if it is less than
			//the element to the left, then swap the two elements using the three-element
			//musical chair dance
			if (target[i] < target[i - 1])
			{
				swapContainer = target[i - 1];
				target[i - 1] = target[i];
				target[i] = swapContainer;
			}
		}
		//after the element is in the correct position, move the partitionIndex 1 to the right
		partitionIndex++;
	}
}

//sorts target int array of size target_size
//using bubble sort algorithm
void bubble_sort(int target[], int target_size)
{
	//initializes an ending element to the target_size - 2
	//that is, the ending element is the element before the last element in the array
	//we want this b/c we are going to compare each element with its neighbor to the right
	int j = target_size - 2;
	int swapContainer = 0;

	while (j >= 0)
	{
		//compare each element with the one to the right going down the line, 
		//and if the element on the left is greater than the element on the right swap them
		for (int i = 0; i <= j; i++)
		{
			if (target[i] > target[i + 1])
			{
				swapContainer = target[i + 1];
				target[i + 1] = target[i];
				target[i] = swapContainer;
			}
		}
		//after all of this the very last element should now be the largest; decrement j so that
		//we do not need to check it again
		j--;
	}
}


//exactly what it sounds like
void insertion_sort_driver(int target[], int target_size)
{
	printf("Attempting insertion sort...\n");
	insertion_sort(target, target_size);
	printf("Array sorted.\n");
	print_int_array(target, target_size);
}

//what it sounds like, yo
void bubble_sort_driver(int target[], int target_size)
{
	printf("Attempting bubble sort...\n");
	bubble_sort(target, target_size);
	printf("Array sorted.\n");
	print_int_array(target, target_size);
}