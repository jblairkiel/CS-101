#include <iostream>
#include <string>
#include <fstream>
#include "huffTree.h"

using namespace std;

int main(int agrc, char* argv[]){

	// Open file from command line
	cout << "Reading in characters\n";
	ifstream input;
	string line;
	char charAr[1000];
	for (int i = 0; i < 1000; i++){
		charAr[i] = NULL;
	}
	int pointer = 0;
	//input.open("input2.txt");
    input.open(argv[1]);
	if (input.is_open()){
		while (getline(input, line)){
			for (unsigned int i = 0; i < line.length(); i++){
				charAr[pointer] = line[i];
				pointer++;
			}
		}
	}
	//encoding
	huffTree hTree = huffTree(charAr);
	hTree.createHeap();
	hTree.printTraversals();
	hTree.createEncodingTable();
	hTree.printEncodingLength();
	hTree.printOriginalText(charAr);
	hTree.printBinary(charAr);

}

