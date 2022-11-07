//***************************************************************************//
//**
//**  Simple Heap implementation - With solution
//**    Copyright 2016 - Aaron S. Crandall
//**
//**
//***************************************************************************//

#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include <stdexcept>      // std::out_of_range
#include <math.h>         // pow()
using namespace std;


template<typename T>
class Heap
{

private:
	vector<T> _items;    // Main vector of elements for heap storage

	/**
	 *  Used to take unsorted data and heapify it
	 */
	void buildHeap()
	{
		//changed this stub so that heap is 1-indexed
		for (unsigned int i = _items.size() / 2 - 1; i >= 1; i--)
		{
			percolateDown(i);
		}
	}

/*********************************************************************/
/********************* Microassignment zone *************************/

	/**
	 *  Percolates the item specified at by index down 
     *   into its proper location within a heap.
	 *  Used for dequeue operations and array to heap conversions
	 *  MA TODO: Implement percolateDown!
	 */
	void percolateDown(int index)
	{

		int hole = index;
		//store object to be moved at the sentinel position	
		swap(_items[0], _items[hole]);

		//ensures the hole still has children
		int lesserChild = 0;

		while(hole * 2 <= _items.size()) {
			//which child is smaller?
			if(2 * hole + 1 <= _items.size() && 
					_items[2 * hole + 1] < _items[2 * hole]) {
				
				lesserChild = 2 * hole + 1;
			}
			else {
				lesserChild = 2 * hole;
			}

			//do we move the hole downward?
			if(_items[0] > _items[lesserChild]) {
				swap(_items[hole], _items[lesserChild]);
				hole = lesserChild;
			}
			else {
				break;
			}
		}

		//fill hole
		swap(_items[0], _items[hole]);
	}

	/**
	 *  Percolate up from a given index to fix heap property
	 *  Used in inserting new nodes into the heap
	 *   MA TODO: Implement percolateUp
	 */
	void percolateUp( int current_position )
	{
		int hole = current_position;
		
		//store temporary value in sentinel index (0)
		swap(_items[0], _items[hole]);
		
		while(hole > 1) {
			//check parent
			if(_items[hole / 2] > _items[0]) {
				swap(_items[hole], _items[hole / 2]);
				hole /= 2;
			}
			else {
				break;
			}
		}
		//fill hole back in
		swap(_items[hole], _items[0]);

	}

/************************** Microassigment zone DONE *********************/

public:
	/**
	 *  Default empty constructor
	 */
	Heap()
	{
		_items.clear();
		//because heap is 1-indexed, place sentinel value at index 0
		_items.push_back(T(0));

	}

	/**
	 *  Constructor with a vector of elements
	 */
	Heap(const vector<T> &unsorted)
	{
		//because heap is 1-indexed, place sentinel value at index 0
		_items.push_back(T(0));

		for (unsigned int i = 0; i < unsorted.size(); i++)
		{
			_items.push_back(unsorted[i]);
		}
		buildHeap();
	}

	/**
	 *  Adds a new item to the heap
	 */
	void insert(T item)
	{
		//because heap is 1-indexed, and size() returns number of
		//non-sentinel values in the array (count starting from 1),
		//index of any new element will be at size() + 1
		unsigned int current_position = size() + 1; // Get index location
		_items.push_back(item);                     // Add data to end
		percolateUp( current_position );            // Adjust up, as needed
	}


	/** 
	 * Returns the top-most item in our heap without 
	 *  actually removing the item from the heap
	 */
	T& getFirst()
	{
		//changed this so that heap is 1-indexed
		if( size() > 1 )
			return _items[1];
		else
			throw std::out_of_range("No elements in Heap.");
	}


	/**
	 *  Removes minimum value from heap and returns it to the caller
	 */
	T deleteMin()
	{
		int last_index = size();             // Calc last item index

		//changed this so that heap is 1-indexed
		int root_index = 1;                      // Root index (for readability)

		T min_item = _items[root_index];         // Keep item to return
		_items[root_index] = _items[last_index]; // Move last item to root
		_items.erase(_items.end() - 1);          // Erase last element entry

		//changed this so that heap is 1-indexed
		percolateDown(1);                        // Fix heap property
		return min_item;

	}


	/**
	 *  Returns true if heap is empty, else false
	 */
	bool isEmpty() const
	{
		//heap will have sentinel value built-in even when empty
		return _items.size() == 1;
	}


	/**
	 *  Returns current quantity of elements in heap (N)
	 */
	int size() const
	{
		//changed this b/c heap is 1-indexed
		return _items.size() - 1;
	}

	/**
	 *  Return heap data in order from the _items vector
	 */
	string to_s() const
	{
		string ret = "";
		//changed this so that heap is 1-indexed
		for(unsigned int i = 1; i < _items.size(); i++)
     	{
			ret += to_string(_items[i]) + " ";
		}
		return ret;
	}

	/**
	 *  Print out the data in order from the _items vector
	 */
	void print() const
	{
		//changed this so that heap is 1-indexed
		for(int i = 1; i < _items.size(); i++)
     	{
			cout << _items[i] << " ";
		}

	}

	/**
	 *  Print out the data with array index details from the _items vector
	 */
	void printArray() const
	{
		//changed this so that heap is 1-indexed
		for(unsigned int i = 1; i <= size(); i++)
		{
			cout << "  [x] Heap element [" << i << "]. key=" 
			     << _items[i] << endl;
		}
	}

	/**
 	 *  Print out the tree by levels (kinda pretty?)
 	 */
	void printPretty() const
	{
		int rownum = 1;
		cout << "   [x] Row #" << rownum  << " -    ";
		//changed this so that heap is 1-indexed
		for( unsigned int i = 1; i <= size(); i++ )
		{
			cout << _items[i] << " ";
			if( pow(2, rownum) - 1 == i )
			{
				rownum++;
				cout << endl << "   [x] Row #" << rownum  << " -    ";
			}
		}
		cout << endl;
	}
};

#endif
