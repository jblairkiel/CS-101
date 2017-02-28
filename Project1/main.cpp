#include <cmath>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <cstring>
#include "Hashtable.h"

using namespace std;

/********************************
 * Project 1 
 * Blair Kiel
 * Dr. Dixon Spring 2015
 *******************************/

string cleanString(string inString);

int main(int argc, char* argv[]){

	ifstream ifInput;
	string inLine;

	//input.open(argv[2]);
	Hashtable hTable = Hashtable(6000);
	//ifInput.open("sample.txt");
	ifInput.open(argv[1]);
	if (ifInput.is_open()){

		// while more lines exist
		while (getline(ifInput, inLine)){

			// parse
			int pointLen = inLine.length();
			int point = 0;
			string strWord;
//istringstream ss(str);
        //int num;
//while(ss >> num)
			while(point < pointLen){
				while (inLine[point] != ' ' && point < pointLen){
					strWord += inLine[point];
					point++;
				}
				point++;
				//Proccess strint
				//out << strWord << "| " << cleanString(strWord) << "\n";
				hTable.put(strWord);
				strWord = "";
			}
		}
	}
	bool continuePrompt = true;
	string strInput;
	while(continuePrompt){
		cout << "Please enter a word: ";
		cin >> strInput;
		cout << "The word '" << strInput << "' appears " << hTable.get(strInput) << " time(s) in the document.\n\n";
	}
	return 0;
}

string cleanString(string inString){

	string strClean = "";
	string strAlpha = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	for(int i = 0; i < inString.length(); i++){
		if(strAlpha.find(inString[i]) != string::npos){
			strClean += tolower(inString[i]);
		}
	}
	return strClean;
}
