#ifndef TWEET_H_
#define TWEET_H_

#include <string>

using namespace std;
/** @brief An Unimplemented class for a Tweet using a linked list.
	This stores the creation date, tweet text, screename and a pointer to another tweet.
*/
class Tweet{

public:

	Tweet();

	// Default Constructor of the linked list
	// Deconstructor
	~Tweet();

	// Removes the first element from the linked
	// list and returns it
	string removeFront();

	// Add to the front of the linked list
	void insertFront(string c);

	// Returns the element stored at the front of the linked list
	string front() const;

	// Returns the number of elements returned
	int count() const;

	// Returns a string representation of the linked list
	std::string toString();

private:

	string data;
	Tweet* next;
	string createdAt;
	string tweetText;
	string screenName;

};

/** @brief The destructor for the Tweet class.
*/
Tweet::~Tweet(){

	Tweet *node = next;
	while (next != NULL){
		next = node->next;
		node = NULL;
		delete node;
		node = next;
	};

	next = NULL;
}
/** @brief The constructor for the Tweet class.
*/
Tweet::Tweet(){
	string data = "";
	next = NULL;
}

/** @brief Removes the Tweet at the front of the Linked List
*/
string Tweet::removeFront(){

	Tweet *temp = next;
	string temp2 = data;
	data = temp->data;
	next = temp->next;
	return temp2;

	/*LinkedList *temp = next;
	char temp1 = data;
	char temp2 = temp->data;
	delete this;
	this->next = temp->next;
	this->data = temp2;
	return temp1;
	*/
}

/** @brief Inserts a new Tweet at the front of the Linked List
	@param c The text of the tweet to be stored.
*/
void Tweet::insertFront(string c){


	Tweet *node = new Tweet();
	node->next = next;
	node->data = data;
	data = c;
	next = node;
	return;


	/*char temp = this->data;
	LinkedList *temp1 = this->next;
	LinkedList* a = LinkedList(temp);
	a->next = temp1;
	delete this;
	data = c;
	next = a;
	*/
}

/** @brief Returns the first Tweet of the Linked List.
*/
string Tweet::front() const{
	return data;
}

/** @brief Returns the number of tweets in the Linked List.
*/
int Tweet::count() const{

	Tweet *node = this->next;
	if (node->data == ""){
		return 0;
	}

	int count = 0;
	while (node->data != ""){
		count++;
		node = node->next;
	}
	return count;
}

/** @brief Prints the Tweets that are linked.
*/
std::string Tweet::toString(){

	Tweet *node = this;
	string str;
	if (node->data == ""){
		return str;
	}
	while (node->data != ""){
		str += node->data;
		node = node->next;
	}
	return str;
}

#endif