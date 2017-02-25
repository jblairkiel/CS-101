#ifndef HASHTABLE_H_
#define HASHTABLE_H_

//We were instructed to use the current time so I had to use the library ctime and chrono
#include <chrono>
#include <ctime>
#include <string>
#include <iostream>

using namespace std;
/** @brief The data structure that contains Tweets.
	Uses djp2 hashing to store tweets in buckets that have tweet cells linked together to prevent collisions.
*/
class Hashtable {

	private:

		struct Cell {
			string key;	//key is the screenname
			int value;	//value is tweet text data 
		};

		Cell **buckets; 	//dynamic array of pointers to the cells
		int nBuckets;		//number of buckets in the array
		int count;		//number of entries in Hashtable
		int uniqueCount;

		Cell *findCell(int nBucket, string nKey){
			Cell *cp = buckets[nBucket];
			if (cp != NULL){
				return cp;
			}
			else{
				return NULL;
			}
		}

	const int seed = 5381;
	const int multiplier = 33;
	const int mask = unsigned(-1) >> 1;


	public:

		Hashtable(int nBuckets);
		~Hashtable();
		void clear();
		void put(string key);
		int get(string key);
		bool contains(string key);
		int getCount();
		int getUniqueCount();
		void remove(string key);
		int hashCode(const string & key);
		void printTweets(string key);
		int getCurrentTime();
		
		
};



#endif
