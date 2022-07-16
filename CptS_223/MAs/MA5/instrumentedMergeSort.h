/***************************************************************************
 *
 *  Sorting algorithms and counting work - Merge sort algorithm
 *   Aaron S. Crandall, 2017 <acrandal@gmail.com>
 *   For Educational use only
 *
 *  This .h provides an instrumented mergesort
 *
 */

#ifndef __INSTRUMENTEDMS_H
#define __INSTRUMENTEDMS_H

#include <vector>
#include <ctime>
#include "main.h"   // For SortStats struct definiton

using namespace std;

vector<int> mergeUs(vector<int> left, vector<int> right) {
    vector<int> result;
    int i = 0;
    int j = 0;

    //both lists still have entries
    while(i < left.size() && j < right.size()) {
        if(left[i] <= right[j]) {
            result.push_back(left[i]);
            i++;
        }
        else {
            result.push_back(right[j]);
            j++;
        }
    }

    //only one list (at most) still has entries remaining at this point
    while(i < left.size()) {
        result.push_back(left[i]);
        i++;
    }
    while (j < right.size()) {
        result.push_back(right[j]);
        j++;
    }

    return result;
}

vector<int> mergeSort(vector<int> & a, int left, int right) {
    vector<int> temp;
    
    //one and two element subvector situations
    if(left == right) {
        temp.push_back(a[left]);
    }
    else if(right - left == 1) {
        temp.push_back(a[left]);
        temp.push_back(a[right]);
        if(temp[0] > temp[1]) {
            swap(temp[0], temp[1]);
        }
    }
    else {
        //recursively mergesort left and right halves
        vector<int> tempLeft = mergeSort(a, left, (left + right) / 2);
        vector<int> tempRight = mergeSort(a, (left + right) / 2 + 1, right);

        //recombine both lists
        temp = mergeUs(tempLeft, tempRight);
    }

    return temp;
}

void instrumentedMergeSort( vector<int> & a, SortStats & stats )
{
    clock_t time_begin = clock();       // Grab presort time


	// MA TODO: Implement Merge Sort plus logging compares and moves/swaps

    a = mergeSort(a, 0, a.size() - 1);

    clock_t time_end = clock();         // Grab time when sort complete
	stats.sortTime = double(time_end - time_begin) / CLOCKS_PER_SEC;
}

#endif