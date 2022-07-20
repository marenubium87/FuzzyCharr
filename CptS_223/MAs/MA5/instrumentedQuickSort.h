/***************************************************************************
 *
 *  Sorting algorithms and counting work - Quicksort algorithm
 *   Aaron S. Crandall, 2017 <acrandal@gmail.com>
 *   For Educational use only
 *
 *  This .h provides an instrumented quicksort
 *
 */

#ifndef __INSTRUMENTEDQS_H
#define __INSTRUMENTEDQS_H

#include <vector>
#include <ctime>
#include "main.h"   // For SortStats struct definiton

using namespace std;

//mid defined as (left + right) / 2, integer truncation
void placePivotAtMid(vector<int> & a, int left, int right, SortStats & stats) {
	int mid = (left + right) / 2;

	if(++stats.compares && a[left] < a[mid]) {
		if(++stats.compares && a[left] > a[right]) {
			//a[left] is the appropriate pivot in this situation
			stats.moves++;
			swap(a[left], a[mid]);
		}
		else {
			//appropriate pivot is the smaller of a[mid] and a[right]
			if(++stats.compares && a[mid] > a[right]) {
				stats.moves++;
				swap(a[mid], a[right]);
			}
		}
	}
	else {
		if(++stats.compares && a[left] < a[right]) {
			//a[left] is the appropriate pivot in this situation
			stats.moves++;
			swap(a[left], a[mid]);
		}
		else {
			//appropriate pivot is the greater of a[mid] and a[right]
			if(++stats.compares && a[mid] < a[right]) {
				stats.moves++;
				swap(a[mid], a[right]);
			}
		}
	}
}

void quickSort(vector<int> & a, int left, int right, SortStats & stats) {
	//one (or less) element (sub)array
	if(++stats.compares && right - left < 1) {
		return;
	}
	//two element (sub)array
	if(++stats.compares && right - left == 1) {
		if(++stats.compares && a[left] > a[right]) {
			stats.moves++;
			swap(a[left], a[right]);
		}
		return;
	}

	placePivotAtMid(a, left, right, stats);

	int i = left;
	int j = right;
	int p = (left + right) / 2;

	//move pointers toward pivots, stopping when a swap is needed
	while(i < j) {
		while(++stats.compares && i < p && a[i] <= a[p]) {
			i++;
		}
		while(++stats.compares && j > p && a[j] >= a[p]) {
			j--;
		}

		//if at least one pointer isn't at the pivot
		if(i != p || j != p) {
			stats.moves++;
			swap(a[i], a[j]);
			//if we moved the pivot, update pivot location
			if(i == p) {
				p = j;
			}
			else if(j == p) {
				p = i;
			}
		}
		//eventually both pointers will be at the pivot and we're done	
	}
	
	quickSort(a, left, p - 1, stats);
	quickSort(a, p + 1, right, stats);
}




void instrumentedQuickSort( vector<int> & a, SortStats & stats )
{
	clock_t time_begin = clock();       // Grab time before the sort

    // MA TODO: implement quicksort and track compares + moves
	quickSort(a, 0, a.size() - 1, stats);

	clock_t time_end = clock();         // Grab time after the sort
	stats.sortTime = double(time_end - time_begin) / CLOCKS_PER_SEC;
}

#endif
