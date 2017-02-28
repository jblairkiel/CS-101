
#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_
/*
 *	A singularly linked list
 */

 #include <string>
 
class LinkedList {

	public:
		// Default Constructor of the linked list
		LinkedList();
		
		// Deconstructor
		~LinkedList();
		
		// Removes the first element from the linked
		// list and returns it
		char removeFront();
		
		// Add to the front of the linked list
		void insertFront(char c);
		
		// Returns the element stored at the front of the linked list
		char front() const;
		
		// Returns the number of elements returned
		int count() const;
		
		// Returns a string representation of the linked list
		std::string toString();
	
	private:

		char data;
		LinkedList* next;
	
};

#endif