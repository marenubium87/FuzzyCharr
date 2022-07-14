/***************************************************************************
 *
 *  Sorting algorithms and counting work - Insertion sort algorithm
 *   Aaron S. Crandall, 2017 <acrandal@gmail.com>
 *   For Educational use only
 *
 *  This .h provides an instrumented insertionsort
 *
 */

#ifndef __INSTRUMENTEDIS_H
#define __INSTRUMENTEDIS_H

#include <vector>
#include <ctime>
#include "main.h"   // For SortStats struct definiton

using namespace std;

void instrumentedInsertionSort( vector<int> & a, SortStats & stats )
{
	clock_t time_begin = clock();           // Grab starting time before sort

	//sorted is the number of elements sorted, AND is also
	//the index of the first unsorted element

	int sorted = 1;
	int j;
	while(sorted < a.size()) {
		j = sorted;
		for(; j > 0; j--) {
			if( ++stats.compares && a[j] < a[j - 1]) {
				stats.moves++;
				swap(a[j], a[j - 1]);
			}
			else {
				break;
			}
		}
		sorted++;
	}

	clock_t time_end = clock();             // Grab ending time after sort
	stats.sortTime = double(time_end - time_begin) / CLOCKS_PER_SEC;
}

#endif
