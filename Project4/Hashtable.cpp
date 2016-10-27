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
}


/** @brief Function that destroys all of the cells in the buckets
*/
void Hashtable::clear(){
	for (int i = 0; i < nBuckets; i++){
		Cell *cp = buckets[i];
		while (cp != NULL){
			Cell *oldCell = cp;
			cp = cp->link;
			delete oldCell;
		}
	}
	count = 0;
}

/** @brief Destructor for the Hashtable, calls clear()
*/
Hashtable::~Hashtable(){
	clear();
}

/** @brief Returns the current time
*/
string Hashtable::getCurrentTime(){
	time_t now;
	time(&now);
	char curTime[26]; 
	ctime(&now); //!Depending on the system, either use ctime_s() or ctime()
	//string curTime;
	//curTime = ctime(&now);
	string tDay;
	string tMonth;
	string tHour;
	string tMin;
	string tSec;
	string tYear;

	tDay.assign(curTime, 8, 2);
	tMonth.assign(curTime, 4, 3);
	if (tMonth == "Jan"){
		tMonth = "01";
	}
	else if (tMonth == "Feb"){
		tMonth = "02";
	}
	else if (tMonth == "Mar"){
		tMonth = "03";
	}
	else if (tMonth == "Apr"){
		tMonth = "04";
	}
	else if (tMonth == "May"){
		tMonth = "05";
	}
	else if (tMonth == "Jun"){
		tMonth = "06";
	}
	else if (tMonth == "Jul"){
		tMonth = "07";
	}
	else if (tMonth == "Aug"){
		tMonth = "08";
	}
	else if (tMonth == "Sep"){
		tMonth = "09";

	}
	else if (tMonth == "Oct"){
		tMonth = "10";
	}
	else if (tMonth == "Nov"){
		tMonth = "11";
	}
	else if (tMonth == "Dec"){
		tMonth = "12";
	}
	tHour.assign(curTime, 11, 2);
	tMin.assign(curTime, 14, 2);
	tSec.assign(curTime, 17, 2);
	tYear.assign(curTime, 20, 4);
	string retTime = tYear + "-" + tMonth + "-" + tDay + "T" + tHour + ":" + tMin + ":" + tSec;
	return retTime;
}

/** @brief Inserts a Tweet's date, value and key into the Hashtable
	The Hashtable will use linkedlists to prevent collisions between the cells
	@param nDate The date that the Tweet was published.
	@param nValue The Tweet's text containing 144 chars.
	@param nKey The Author of the Tweet
*/
void Hashtable::put(string nDate, string nValue, string nKey){
	int hashcode = hashCode(nKey);
	int bucketNum = hashcode % nBuckets;
	if (nKey == "tideladder"){
		nKey = "tideladder";
	}
	Cell *cp = findCell(bucketNum, nKey);
	//If the cell is empty
	if (cp == NULL){
		cp = new Cell;
		cp->date = nDate;
		cp->key = nKey;
		cp->value = nValue;
		cp->cData = nDate + ":" + nValue;
		cp->link = buckets[bucketNum];
		buckets[bucketNum] = cp;
	}
	//If the cell already contains tweets
	else{
		Cell *cd = new Cell;
		//Reordering the list
		//If there is only one element in the list
		if (cp->link == NULL){
			//The existing tweet is newer than the new tweet
			if (!isOlderThan(nDate, cp->date)){
				//move cp's values to cd
				cd->value = cp->value;
				cd->key = cp->key;
				cd->date = cp->date;
				cd->cData = cd->date + ":" + cd->value;
				cd->link = NULL;
				//reassign cp values
				cp->date = nDate;
				cp->value = nValue;
				cp->key = nKey;
				cp->link = cd;
				cp->cData = nDate + ":" + nValue;
			}
			//The existing tweet is older than the new tweet
			else{
				cd->date = nDate;
				cd->value = nValue;
				cd->key = nKey;
				cd->cData = nDate + ":" + nValue;
				cd->link = NULL;
				cp->link = cd;
			}
		}
		//There are multiple elements in the list
		else{
			//The first tweet is older than the new tweet
			if (!isOlderThan(nDate, cp->date)){
				//cp values to cd
				cd->date = cp->date;
				cd->value = cp->value;
				cd->key = cp->key;
				cd->cData = cp->cData;
				cd->link = NULL;
				//new data to cp
				cd->link = cp->link;
				cp->date = nDate;
				cp->value = nValue;
				cp->key = nKey;
				cp->cData = nDate + ":" + nValue;
				cp->link = cd;
			}
			//The first tweet is newer than the new tweet
			else{
				cd->date = nDate;
				cd->value = nValue;
				cd->key = nKey;
				cd->cData = nDate + ":" + nValue;
				cd->link = cp;
				//traverse the list until it finds a tweet that it is younger than 
				bool cont = true;
				while (cont){
					if (isOlderThan(nDate, cd->link->date)){
						if (cd->link->link == NULL){
							cd->link->link = cd;
							cd->link = NULL;
							cont = false;
						}
						else{
							if (cd->link->link != NULL){
								if (!isOlderThan(nDate, cd->link->link->date)){
									Cell *temp = cd->link;
									cd->link = temp->link;
									temp->link = cd;
									cont = false;
								}
								else{
									cd->link = cd->link->link;
								}
							}
						}
					}
					else{
						Cell *temp = cd->link;
						cd->link = temp->link;
						temp->link = cd;
						cont = false;
					}
				}
			}
		}
	}
	count++;
	if (count == 1252){
		count = count;
	}
}

/** @brief Returns the first cell containing the Tweet from an author
	@param nKey The author of the Tweet to search for
*/
string Hashtable::get(string nKey){
	int bucketNum = hashCode(nKey) % nBuckets;
	Cell *cp = findCell(bucketNum, nKey);
	if (cp == NULL){
		cout << "get: no value for the key";
		return NULL;
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

/** @brief Returns True if date1 is older than date2, else return false
	@param date1 The first date to be compared
	@param date2 The second date to be compared
*/
bool Hashtable::isOlderThan(string date1, string date2){
	int point1 = 0;
	int point2 = 0;
	string year1;
	string year2;
	string month1;
	string month2;
	string day1;
	string day2;
	string hour1;
	string hour2;
	string min1;
	string min2;
	string sec1;
	string sec2;

	year1.assign(date1, 0, 4);
	year2.assign(date2, 0, 4);
	if (atoi(year1.c_str()) < atoi(year2.c_str())){
		return true;
	}
	else if (atoi(year1.c_str()) > atoi(year2.c_str())){
		return false;
	}

	month1.assign(date1, 5, 2);
	month2.assign(date2, 5, 2);
	if (atoi(month1.c_str()) < atoi(month2.c_str())){
		return true;
	}
	else if (atoi(month1.c_str()) > atoi(month2.c_str())){
		return false;
	}

	day1.assign(date1, 8, 2);
	day2.assign(date2, 8, 2);
	if (atoi(day1.c_str()) < atoi(day2.c_str())){
		return true;
	}
	else if (atoi(day1.c_str()) > atoi(day2.c_str())){
		return false;
	}

	hour1.assign(date1, 11, 2);
	hour2.assign(date2, 11, 2);
	if (atoi(hour1.c_str()) < atoi(hour2.c_str())){
		return true;
	}
	else if (atoi(hour1.c_str()) > atoi(hour2.c_str())){
		return false;
	}

	min1.assign(date1, 14, 2);
	min2.assign(date2, 14, 2);
	if (atoi(min1.c_str()) < atoi(min2.c_str())){
		return true;
	}
	else if (atoi(min1.c_str()) > atoi(min2.c_str())){
		return false;
	}

	sec1.assign(date1, 17, 2);
	sec2.assign(date2, 17, 2);
	if (atoi(sec1.c_str()) < atoi(sec2.c_str())){
		return true;
	}
	else{
		return false;
	}
}

/** @brief Removes all Tweets by an author
	@param nKey The author of the Tweet's to be removed
*/
void Hashtable::remove(string nKey){
	int hashcode = hashCode(nKey);
	int nBucket = hashcode % nBuckets;
	if (contains(nKey)){

		Cell *temp = new Cell;
		Cell *temp1 = new Cell;
		Cell *cp = buckets[nBucket];
		//If there are more than one key in a bucket
		if ((cp != NULL) && (nKey != cp->key)){
			while ((cp != NULL) && (nKey != cp->key)){
				if ((cp->link == NULL) && (nKey != cp->key)){
					cp = NULL;
				}
				else{
					temp = cp;
					cp = cp->link;
				}
			}
			while ((cp->key == nKey) && (cp->link != NULL)){
				temp1 = cp;
				cp = cp->link;
				delete temp1;
				if (cp->link == NULL){
					temp->link = NULL;
					cp = NULL;
					goto endofloop;
				}
				if (cp != NULL){
					if (cp->key != nKey){
						temp->link = cp;
					}
				}
			}
		}
		//only one key in a bucket
		else{
			buckets[nBucket] = NULL;
		}
	endofloop:
		temp1 = temp1;
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
		while (cp != NULL){
			if (cp->key == nKey){
				cout << cp->cData << "\n";
			}
			cp = cp->link;
		}
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
