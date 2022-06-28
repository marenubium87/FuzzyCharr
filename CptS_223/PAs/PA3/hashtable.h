/**
 *  Basic hash table implementation
 *   Aaron S. Crandall - 2017 <acrandal@gmail.com>
 *
 */

#ifndef __HASH_H
#define __HASH_H

#include <unordered_map>
#include <string>
#include <iostream>
#include <cmath>
#include <list>
#include <vector>
#include <algorithm>

using namespace std;
/*
	private:
		void rehash();
		int hash_function(KEYTYPE key);
		
	public:
		bool insert(KEYTYPE key, VALTYPE val);
		bool contains(KEYTYPE key);
		int remove(KEYTYPE key);
		VALTYPE & find(KEYTYPE key);
		int size();            // Elements currently in table
		bool empty();          // Is the hash empty?
		float load_factor();   // Return current load factor
		void clear();          // Empty out the table
		int bucket_count();    // Total number of buckets in table
*/

template <typename KEYTYPE, typename VALTYPE>
class Hashtable
{
	private:
		int numEntries;
		int buckets;
		vector<list<VALTYPE>> table;

		/**
		 *  Rehash the table into a larger table when the load factor is too large
		 *  done for now
		 */
		void rehash() {
			vector<list<VALTYPE>> temp = move(table);
			table.clear();
			numEntries = 0;
			buckets = findNextPrime(buckets);
			table.resize(buckets);

			for(list<VALTYPE> bucketList : temp) {
				if(!bucketList.empty()) {
					for(VALTYPE word : bucketList) {
						insert(word.myword, word);
					}
				}
			}
		}

		/**
		 *  Function that takes the key (a string or int) and returns the hash key
		 *   This function needs to be implemented for several types it could be used with!
		 *  Done for now
		 */
		unsigned int hash_function(unsigned int key) {
			
			unsigned int hashKey = 0;
			unsigned int nextDigit = 0;
			int i = 1;
			do {
				nextDigit = key % 10;
				hashKey += nextDigit * pow(37, i);
				key = key / 10;
				i++;
			} while(key != 0);
			cout << "hashkey is " << hashKey % buckets << endl;
			return hashKey % buckets;
		}

		unsigned int hash_function(string key) {
			
			unsigned int hashKey = 0;
			for(int i = 0; i < key.length() - 1; i++) {
				hashKey += key[key.length() - i - 1] * pow(37, i);
			}
			return hash_function(hashKey);
		}

		/*returns first prime number greater than target
		* required to rehash
		* done for now
		*/
		int findNextPrime(int target) {
			if(target < 2) {
				return 2;
			}

			int primeCandidate = target;

			if(primeCandidate % 2 == 0) {
				primeCandidate++;
			}
			//so now primeCandidate is odd
			while(!isPrime(primeCandidate)) {
				primeCandidate += 2;
			}

			return primeCandidate;
		}

		/*returns true if target is prime
		* required for findNextPrime
		* done for now
		*/
		bool isPrime(int target) {
			if(target < 2) {
				return false;
			}
			//no even numbers
			if(target % 2 == 0) {
				return false;
			}
			//first few primes
			if(target == 2 || target == 3 || target == 5 || target == 7) {
				return true;
			}
			//threshold is just greater than square root of target
			//check odd possible divisors of target up to threshold
			int threshold = ceil(sqrt(target));
			int i = 3;
			while(i <= threshold) {
				if(target % i == 0) {
					return false;
				}
				i += 2;
			}
			return true;
		}
		
	public:
		/**
		 *  Basic constructor
		 */
		Hashtable( int startingSize = 101 )
		{
			numEntries = 0;
			buckets = startingSize;
			table.resize(buckets);
		}

		/**
		 *  Add an element to the hash table
		 *  returns 0 if value was successfully inserted
		 *  returns 1 if value was already in table (overwriting)
		 *  hash is based on ALL LOWERCASE versions of the word
		 *  e.g. 'hELlo' is hashed based on 'hello'
		 *  done for now
		 */
		bool insert(KEYTYPE key, VALTYPE val) {

			transform(key.begin(), key.end(), key.begin(), 
				[](unsigned char c) {return tolower(c);});

			bool wordAlreadyPresent = false;
			//is the word already present?
			if (contains(key)) {
				for(VALTYPE word : table[hash_function(key)]) {
					if(word == val) {
						//modify word if found
						word.myword = val.myword;
						word.definition = val.definition;
						break;
					}
				}
			}
			else {
				numEntries++;

				table[hash_function(key)].push_front(val);

				//check load factor
				if(load_factor() > 1) {
					rehash();
				}
				return 0;
			}
			return 1;
		}

		/**
		 *  Return whether a given key is present in the hash table
		 *  done for now
		 */
		bool contains(KEYTYPE key) {

			transform(key.begin(), key.end(), key.begin(), 
				[](unsigned char c) {return tolower(c);});

			int hashKey = hash_function(key);
			if(!table[hashKey].empty()) {
				for(VALTYPE word : table[hashKey]) {
					string temp = word.myword;
					transform(temp.begin(), temp.end(), temp.begin(), 
							[](unsigned char c) {return tolower(c);});
					if (temp == key) {
						return true;
					}
				}
			}
			return false;
		}


		/**
		 *  Completely remove key from hash table
		 *   Returns number of elements removed
		 */
		int remove(KEYTYPE key) {

			transform(key.begin(), key.end(), key.begin(), 
				[](unsigned char c) {return tolower(c);});

			int numElementsRemoved = 0;
			if(contains(key)) {
				typename list<VALTYPE>::iterator it = 
						table[hash_function(key)].begin();

				for(; it != table[hash_function(key)].end(); it++) {
					string temp = it->myword;
					transform(temp.begin(), temp.end(), 
							temp.begin(), 
							[](unsigned char c) {return tolower(c);});

					if(temp == key) {
						break;
					}
				}
				table[hash_function(key)].erase(it);
				numElementsRemoved++;
			}

			numEntries -= numElementsRemoved;
			return numElementsRemoved;
		}

		/**
		 *  Searches the hash and returns a pointer
		 *   Pointer to Word if found, or nullptr if nothing matches
		 */
		VALTYPE *find(KEYTYPE key) {

			transform(key.begin(), key.end(), key.begin(), 
				[](unsigned char c) {return tolower(c);});

			if(contains(key)) {
				for(VALTYPE word : table[hash_function(key)]) {
					string temp = word.myword;
					transform(temp.begin(), temp.end(), 
							temp.begin(), 
							[](unsigned char c) {return tolower(c);});
					if(temp == key) {
						VALTYPE * pWord = &word;
						return pWord;
					}
				}
			}
			return nullptr;
		}

		/**
		 *  Return current number of elements in hash table
		 *  done for now
		 */
		int size() {
			return numEntries;
		}

		/**
		 *  Return true if hash table is empty, false otherwise
		 *  done for now
		 */
		bool empty() {
			return numEntries == 0;
		}

		/**
		 *  Calculates the current load factor for the hash
		 *  done for now
		 */
		float load_factor() {
			return (float) (numEntries / buckets);
		}

		/**
		 *  Returns current number of buckets (elements in vector)
		 *  done for now
		 */
		int bucket_count() {
			return buckets;
		}

		/**
		 *  Deletes all elements in the hash
		 *  done for now
		 */
		void clear() {
			table.clear();
			numEntries = 0;
			buckets = 101;
			table.resize(buckets);
		}

};


#endif
