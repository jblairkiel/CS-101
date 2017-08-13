
#include <iostream>
#include <fstream>

#include "LinkedList.h"

int main(int argc, char* argv[]) {
	
	if(argc != 2) {
		std::cout << "\nPlease profile a file to read in values\n";
		std::cout << "\nUsage: " << argv[0] << " <filename>" << std::endl;
		return 1;
	}
	
	/*Removed carrots, because they are used in
	comparisons and points which do not match*/
	char mappings[3][2] = {
		//{'<','>'},
		{'(',')'},
		{'[',']'},
		{'{','}'}
	};
	
	LinkedList l;
	
	std::ifstream input(argv[1]);
	
	char c;
	
	while(input >> c) {
		for( int i = 0 ; i < 4; ++i) {
			if( mappings[i][0] == c ) { 		// opening brace
				l.insertFront(c);
				break;
			} else if( mappings[i][1] == c ) {	// closing brace
				
				if(l.count() == 0 ) {
					std::cout << "Reached closing brace with no matching open brace: " << c << std::endl;
					input.close();
					return 1;
				}
				
				if( l.front() != mappings[i][0]) {
					std::cout << "Found '" << c << "' but expected closing brace for '" << l.front() << "'" << std::endl;
					std::cout << "Remaining braces: " << l.toString() << std::endl;
					input.close();
					return 1;
				}
				l.removeFront();
				break;
			}
		}			
	}
	input.close();
	
	if( l.count() == 0 ) {
		std::cout << "Valid program" << std::endl;
	}else {
		std::cout << "Did not close all braces" << std::endl;
		std::cout << "Remaining braces to close: " << l.toString() << std::endl;
		return 1;
	}
	return 0;
}
