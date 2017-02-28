#include <iostream>
#include <string>
#include <fstream>
#include "huffTree.h"

using namespace std;

int main(int agrc, char* argv[]){

	// Open file from command line
	cout << "Reading in files";

	//decoding
	string treeFile = "tree.txt";
	string codeFile = "code.txt";
	huffTree hTree = huffTree(treeFile, codeFile);
	hTree.constructTree();
	//hTree.createEncodingTable();
	hTree.decode();
	int a = 0;
}

