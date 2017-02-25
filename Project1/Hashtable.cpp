#include "Hashtable.h"
#include <iostream>
#include <cstring>
#include <cstdlib>

/** @brief Constructor for a Hashtable that stores
*	@param bucketsNum The number of "buckets the Hashtable will contain
*/
Hashtable::Hashtable(int bucketsNum){
	nBuckets = bucketsNum; 
	buckets = new Cell*[nBuckets];
	for (int i = 0; i < nBuckets; i++){
		buckets[i] = NULL;
	}
	count = 0;
	uniqueCount = 0;
}


/** @brief Function that destroys all of the cells in the buckets
*/
void Hashtable::clear(){
	for (int i = 0; i < nBuckets; i++){
		Cell *cp = buckets[i];
		delete cp;
	}
	count = 0;
}

/** @brief Destructor for the Hashtable, calls clear()
*/
Hashtable::~Hashtable(){
	clear();
}

/** @brief Inserts a Tweet's date, value and key into the Hashtable
	The Hashtable will use linkedlists to prevent collisions between the cells
	@param nDate The date that the Tweet was published.
	@param nValue The Tweet's text containing 144 chars.
	@param nKey The Author of the Tweet
*/
void Hashtable::put(string nKey){
	int hashcode = hashCode(nKey);
	int bucketNum = hashcode % nBuckets;
	if (nKey == "tideladder"){
		nKey = "tideladder";
	}
	Cell *cp = findCell(bucketNum, nKey);
	//If the cell is empty
	if (cp == NULL){
		cp = new Cell;
		cp->key = nKey;
		cp->value = 1;
		buckets[bucketNum] = cp;
		uniqueCount++;
	}
	//If the cell already contains tweets
	else{
		cp->value++;
	}
	count++;
	/*if (count == 1252){
		count = count;
	}*/
}

/** @brief Returns the first cell containing the Tweet from an author
	@param nKey The author of the Tweet to search for
*/
int Hashtable::get(string nKey){
	int bucketNum = hashCode(nKey) % nBuckets;
	Cell *cp = findCell(bucketNum, nKey);
	if (cp == NULL){
		cout << 0;
		return 0;
	}
	else{
		return cp->value;
	}
}

/** @brief Returns True if the Hashtable contains Tweets from an author
	@param nKey The author of the Tweet being searched for
*/
bool Hashtable::contains(string nKey){
	int hashcode = hashCode(nKey);
	int nBucket = hashcode % nBuckets;
	return findCell(nBucket, nKey) != NULL;
}

/** @brief Returns the number of Tweets in the hashtablek
*/
int Hashtable::getCount(){
	return count;
}

/** @brief Returns the unique count of the hashtable
*/
int Hashtable::getUniqueCount(){
	return uniqueCount;
}

/** @brief Removes all Tweets by an author
	@param nKey The author of the Tweet's to be removed
*/
void Hashtable::remove(string nKey){
	int hashcode = hashCode(nKey);
	int nBucket = hashcode % nBuckets;
	if (contains(nKey)){

		Cell *cp = buckets[nBucket];
		delete cp;
	}
	else{
		cout << "There are no tweets to delete from: " << nKey << "\n";
	}
}

/** @brief Prints the Tweet's of an author.
	If the author's Tweet's do not exist, prints "There are not tweets to print from: <author>"
	@param nKey The author of the Tweet's to be printed.
*/
void Hashtable::printTweets(string nKey){
	int bucketNum = hashCode(nKey) % nBuckets;
	if (contains(nKey)){
		Cell *cp = findCell(bucketNum, nKey);
		cout << cp->value << "\n";
	}
	else{
		cout << "There are no tweets to print from: " << nKey << "\n";
	}
}
/** @brief The djb2 hashcode algorithm.
	Takes a string value to be converted, in this case the author of the Tweets, and returns a complex integer which will be the number of the bucket to store the tweet it.
	@param value The author of the tweet to be converted to an integer.
*/
int Hashtable::hashCode(const string & value){
	unsigned hash = seed;
	int n = value.length();
	for (int i = 0; i < n; i++){
		hash = multiplier * hash + value[i];
	}
	int returnValue = int(hash & mask);
	return returnValue;
}
