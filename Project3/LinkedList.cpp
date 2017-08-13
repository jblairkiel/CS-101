
#include "LinkedList.h"
#include <stdexcept>

LinkedList::LinkedList() {
	next = NULL;
}

LinkedList::~LinkedList() {
	if(next != NULL) {
		delete next;
		next = NULL;
	}
}


// Removes the first element from the linked
// list and returns it
char LinkedList::removeFront() {
	if(count() == 0) throw std::runtime_error("Error, removing from an empty linked list");
	
	char result = next->data;
	
	// Free memory
	LinkedList* t = next;
	next = t->next;
	t->next = NULL;
	delete t;
	
	return result;
}

// Add to the front of the linked list
void LinkedList::insertFront(char c) {
	LinkedList *val = new LinkedList();
	val->data = c;
	val->next = next;
	next = val;
}

// Returns the element stored at the front of the linked list
char LinkedList::front() const {
	if(count() == 0) {
		throw std::runtime_error("Error, trying to retrieve the front of an empty linked list");
	}else{
		return next->data;
	}
}

// Returns the number of elements returned
int LinkedList::count() const {
	if(next == NULL){
		return 0;
	}else{
		return 1 + next->count();
	}
}

// Returns a string representation of the linked list
std::string LinkedList::toString() {
	if(count() == 0){
		return "";
	}else{
		return std::string(1,next->data) + " " +  next->toString();
	}
}

