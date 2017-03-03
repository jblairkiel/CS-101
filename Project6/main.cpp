#include <iostream>
#include <string>
#include <fstream>
#include "DGraph.h"

using namespace std;

int main(int agrc, char* argv[]){

	// Open file from command line
	cout << "Reading in characters\n";
	ifstream input;
	string line;
	int pointer = 0;
	DGraph graph;

	//input.open("input2.txt");
    	input.open(argv[1]);
	if (input.is_open()){
		int IOState = 0;
		int lineCount = 0;
		int spaceCounter = 0;
		string startEndVert = "";
		string val1 = "";
		string val2 = "";
		string val3 = "";
		while (getline(input, line)){
			if(IOState == 0){
				if(line.length() == 0){
					IOState++;
					spaceCounter = 0;
					val1 = val2 = "";
					//cout << "\n";
				}
				else{
					for (unsigned int i = 0; i < line.length(); i++){
						if(spaceCounter == 0){
							if(line[i] == ' '){ spaceCounter++;} else { val1 += line[i];}
						}
						else if(spaceCounter == 1){
							val2 += line[i];	
						}
						pointer++;
					}
					//cout << "Val1 is: " << val1 << " | Val2 is: " << val2 << "\n";
					graph.initialize(stoi(val1), stoi(val2));
					val1 = val2 = "";
				}
			}	
			
			else if(IOState == 1){
				if(line.length() == 0){
					IOState++;
					spaceCounter = 0;
					//cout << "\n";
				}
				else{
					for (unsigned int i = 0; i < line.length(); i++){
						if(spaceCounter == 0){
							if(line[i] == ' '){ spaceCounter++; i++; } else { val1 += line[i];}
						}
						else if (spaceCounter == 1){
							if(line[i] == ' '){ spaceCounter++;} else { val2 += line[i];}	
						}
						else if (spaceCounter == 2){
							val3 += line[i];
						}
						pointer++;
					}
					//cout << "Val1 is: " << val1 << " | Val2 is: " << val2 << " | Val3 is: " << val3 << "\n";
					graph.addVertex(stoi(val1), stoi(val2), stoi(val3));
					val1 = val2 = val3 = "";
					spaceCounter = 0;
				}
			}
			
			else if(IOState == 2){
				if(line.length() == 0){
					IOState++;
					spaceCounter = 0;
					getline(input,line);
					//cout << "\n";
				}
				for (unsigned int i = 0; i < line.length(); i++){
					if(spaceCounter == 0){
						if(line[i] == ' '){ spaceCounter++;} else { val1 += line[i];}
					}
					else if (spaceCounter == 1){
						val2 += line[i];
					}
					pointer++;
				}
				//cout << "Val1 is: " << val1 << " | Val2 is: " << val2 << "\n";
				graph.addEdge(stoi(val1), stoi(val2));
				startEndVert = val1 + val2;
				val1 = val2 = "";
				spaceCounter = 0;
			}
			else if(IOState == 3){
				for (unsigned int i = 0; i < line.length(); i++){
					if(spaceCounter == 0){
						if(line[i] == ' '){ spaceCounter++;} else { val1 += line[i];}
					}
					else if (spaceCounter == 1){
						val2 += line[i];
					}
					pointer++;
				}
				//cout << "Val1 is: " << val1 << " | Val2 is: " << val2 << "\n";
				startEndVert = val1 + val2;
				spaceCounter = 0;
			}
			lineCount++;
		}
	}
	//
	graph.djikstra(val1, val2);
	//encoding
	/*
	huffTree hTree = huffTree(charAr);
	hTree.createHeap();
	hTree.printTraversals();
	hTree.createEncodingTable();
	hTree.printEncodingLength();
	hTree.printOriginalText(charAr);
	hTree.printBinary(charAr);
	*/

}

