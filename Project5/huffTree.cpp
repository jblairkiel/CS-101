#include <string>
#include <fstream>
#include <iostream>
#include "huffTree.h"

using namespace std;

huffTree::huffTree(string treeFile, string codeFile){
	hArray = new hNode*[1000];
	char foundArr[1000];
	randomIntCount = 500;
	encodingCounter = 0;
	encodingLength = 0;
	decodeCount = 0;
	tempCount = 1;

	tFile = treeFile;
	cFile = codeFile;

	//initialize hArray
	for (int a = 0; a < 1000; a++){
		hArray[a] = NULL;
	}

	//initialize foundArr
	for (int b = 0; b < 1000; b++){
		foundArr[b] = NULL;
	}

	//initialize encodingTable
	for (int c = 0; c < 1000; c++){
		encodingTable[c] = "";
	}
}

huffTree::huffTree(char charAr[1000]){

	hArray = new hNode*[1000];
	char foundArr[1000];
	top = hArray[0];
	randomIntCount = 500;
	encodingCounter = 0;
	encodingLength = 0;

	//initialize hArray
	for (int a = 0; a < 1000; a++){
		hArray[a] = NULL;
	}

	//initialize foundArr
	for (int a = 0; a < 1000; a++){
		foundArr[a] = NULL;
	}

	//initialize encodingTable
	for (int b = 0; b < 1000; b++){
		encodingTable[b] = "";
	}

	
	
	//pass the characters into the temparray 
	int i = 0;
	int count = 0;
	int foundCount = 0;
	//go through the array for each int
	while (charAr[i] != NULL){ 
		bool notSeen = true;
		int j = 0;
		//check if it was already counted
		if (isdigit(charAr[i])){
			goto foundNum;
		}
		while (foundArr[j] != NULL){ 
			if (charAr[i] == foundArr[j]){
				notSeen = false;
			}
			j++;
		}

		// it has not been seen so count how many times it is used
		if (notSeen){
			int k = 0;
			while (charAr[k] != NULL){
				if (charAr[i] == charAr[k]){
					count++;
				}
				k++;
			}
			//add the found count to the temp aray
			int temp = 0;
			while (foundArr[temp] != NULL){
				temp++;
			}
			char wordToAdd = charAr[i];
			foundArr[temp] = charAr[i];

			//insert node to heap
			insertChar(charAr[i], count);
			foundCount++;
		}
foundNum:
		count = 0;
		i++;
	}

	//initialize lenght of array
	lenOfArray = 0;
	while (hArray[lenOfArray] != NULL){
		lenOfArray++;
	}
}

hNode* huffTree::buildTree(hNode* node, string temp[]){
	if (temp[tempCount] != ""){
		//if internal traverse left
		if (temp[tempCount][0] == 'I'){
			hNode *nNode = new hNode;
			nNode->value = temp[tempCount].substr(2, sizeof(temp[tempCount]));
			tempCount++;
			node->left = buildTree(nNode, temp);
		}
		//	if leaf print left
		else{
			hNode *nNode = new hNode;
			nNode->value = convertFromASCII(temp[tempCount].substr(2, sizeof(temp[tempCount])));
			node->left = nNode;
			tempCount++;
		}
		//print node
		//if internal traverse right
		if (temp[tempCount][0] == 'I'){
			hNode *nNode = new hNode;
			nNode->value = temp[tempCount].substr(2, sizeof(temp[tempCount]));
			tempCount++;
			node->right = buildTree(nNode, temp);
		}
		//	if leaf print right
		else{
			hNode *nNode = new hNode;
			nNode->value = convertFromASCII(temp[tempCount].substr(2, sizeof(temp[tempCount])));
			node->right = nNode;
			tempCount++;
		}
		return node;
	}
	else{
		return NULL;
	}
}
void huffTree::constructTree(){

	//25pts this constructs a tree from the tree.txt
	ifstream f;
	f.open(tFile);
	string treeString;
	string temp[1000];
	for (int i = 0; i < 1000; i++){
		temp[i] = "";
	}
	getline(f, treeString);
	int count = 0;
	string tempString = "";
	for (int j = 0; j < treeString.length(); j++){
		if ((treeString[j] == ' ') && (treeString[j - 1] != ':')){
			temp[count] = tempString;
			tempString = "";
			count++;
		}
		else{
			tempString += treeString[j];
		}
	}
	hNode *root = new hNode;
	root->value = temp[0].substr(2, sizeof(temp[0]));
	hArray[0] = root;
	hArray[0] = buildTree(hArray[0], temp);

	//compute lenght of array
	lenOfArray = 0;
	while (hArray[lenOfArray] != NULL){
		lenOfArray++;
	}
}

void huffTree::decode(){
	
	//25pts to decode a tree.txt and code.txt
	ifstream f;
	string iString;
	string codeString = "";
	f.open(cFile);
	//read in the code text to decode from the tree that was just built
	if (f.is_open()){
		while (getline(f, iString)){
			codeString = codeString + iString;
		}
	}

    cout << "\n";
	while (decodeCount < codeString.length()-1){
		decodeTraverse(hArray[0], codeString);
	}
	int a = 0;
}

void huffTree::decodeTraverse(hNode* node, string text){
	hNode *nNode = node;
	while (true){
		if (text[decodeCount] == '0'){
			if (isdigit(nNode->value[0])){
				nNode = nNode->left;
				if (decodeCount < text.length()-1){
					decodeCount++;
				}
			}
			else{
				cout <<	nNode->value;
				return;
			}
		}
		else if (text[decodeCount] == '1'){
			if (isdigit(nNode->value[0])){
				nNode = nNode->right;
				if (decodeCount < text.length()-1){
					decodeCount++;
				}
			}
			else{
				cout << nNode->value;
				return;
			}
		}
	}
}

void huffTree::printBinary(char charAr[1000]){
	// +5pts to print the true binary code
	ofstream f("code.bin");
	int i = 0;
	while (charAr[i] != NULL){
		int bin = 0x80;
		while (bin > 0){
			if ((charAr[i] & bin) > 0){
				f << "1";
			}
			else{
				f << "0";
			}
			bin >>= 1;
		}
		i++;
	}
	f.close();
}

void huffTree::printOriginalText(char charAr[1000]){
	ofstream f("code.txt");
	string oCode = "";
	int i = 0;
	//loop through the original text and compare it to the encoding table
	while (charAr[i] != NULL){
		int j = 0;
		while (encodingTable[j] != ""){
			if (encodingTable[j][0] == charAr[i]){
				oCode = oCode + encodingTable[j].substr(1, encodingTable[j].length());
			}
			j++;
		}
		i++;
	}
	f << oCode;
	f.close();
}

void huffTree::printEncodingLength(){

	ofstream f("length.txt");
	int i = 0;
	//print each leaf node's encoding one at a time
	while (encodingTable[i] != ""){
		int code = 0;
		for (int j = 0; j < encodingTable[i].substr(0, 1).size(); j++){
			code += encodingTable[i].substr(0, 1)[j];
		}
		//ensure it has 3 characters
		int lengthCount = 0;
		int temp = code;
		while (temp)
		{
			temp = temp / 10;
			lengthCount++;
		}

		if (lengthCount == 2){
			string a = to_string(code);
			a.insert(0, "0");
			string sCode = a + " " + to_string((encodingTable[i].substr(1,sizeof(encodingTable[1]))).length()) + "\n";
			f << sCode;
		}
		else{
			string sCode = to_string(code) + " " + to_string((encodingTable[i].substr(1,sizeof(encodingTable[1]))).length()) + "\n";
			f << sCode;
		}
		i++;
	}
	f.close();
}

void huffTree::createEncodingTable(){

	while (encodingLength != lenOfArray){
		string code = "";
		encode(hArray[0], code);
	}
	//order the hArray based on the frequency with selection sort
	int length = 0;
	for (int i = 0; i < 1000; i++){
		if (encodingTable[i] != ""){
			length++;
		}
	}

	int first;
	string temp;
	for (int i = length - 1; i > 0; i--){
		first = 0;
		for (int j = 1; j <= i; j++){
			if ((int)encodingTable[j][0] >= (int)encodingTable[first][0]){
				first = j;
			}
		}
		temp = encodingTable[first];
		encodingTable[first] = encodingTable[i];
		encodingTable[i] = temp;
	}
}

void huffTree::encode(hNode* node, string code){
	if (node){
		//if internal traverse left
		if (node->left != NULL){
			if (isdigit(node->left->value[0])){
				string tempcode = code + "0";
				encode(node->left, tempcode);
			}
			//	if leaf print left
			else{
				if (!isdigit(node->left->value[0])){
					string prevCode = code;
					code.insert(0, node->left->value);
					encodingTable[encodingCounter] = code + "0";
					encodingCounter++;
					encodingLength++;
					node->left = NULL;
					code = prevCode;
				}
			}
		}
		//if internal traverse right
		if (node->right != NULL){
			if (isdigit(node->right->value[0])){
				code = code + "1";
				encode(node->right, code);
			}
			//	if leaf print right
			else{
				if (!isdigit(node->right->value[0])){
					string prevCode = code;
					code.insert(0, node->right->value);
					encodingTable[encodingCounter] = code + "1";
					encodingCounter++;
					encodingLength++;
					node->right = NULL;
					code = prevCode;
				}
			}
		}
	}
}
void huffTree::printTraversals(){

	ofstream f("tree.txt");
	//print preorder
	preorder(hArray[0], f);
	//print inorder
	f << "\n";
	inorder(hArray[0], f);
	f.close();
}

void huffTree::preorder(hNode* node, ofstream &f){

	if (node){
		//print node
		f << "I:" + node->value + " ";
		//if internal traverse left
		if (isdigit(node->left->value[0])){
			preorder(node->left,f);
		}
		else{
			// if leaf print left and right 
			if (!isdigit(node->left->value[0])){
				f << "L:" + convertToASCII(node->left->value) + " ";
			}
			if (!isdigit(node->right->value[0])){
				f << "L:" + convertToASCII(node->right->value)  + " ";
			}
		}
		//if internal traverse right
		if (isdigit(node->right->value[0])){
			preorder(node->right,f);
		}
			// if leaf print left and right
		else if ((!isdigit(node->right->value[0])  && (isdigit(node->left->value[0])) )){
			if (!isdigit(node->left->value[0])){
				f << "L:" + convertToASCII(node->left->value) + " ";
			}
			if (!isdigit(node->right->value[0])){
				f << "L:" + convertToASCII(node->right->value) + " ";
			}
		}
	}
}

void huffTree::inorder(hNode* node, ofstream &f){
	if (node){
		//if internal traverse left
		if (isdigit(node->left->value[0])){
			inorder(node->left, f);
		}
		//	if leaf print left
		else{
			if(!isdigit(node->left->value[0])){
				f << "L:" + convertToASCII(node->left->value) + " ";
			}
		}
		//print node
		f << "I:" + node->value + " ";
		//if internal traverse right
		if (isdigit(node->right->value[0])){
			inorder(node->right, f);
		}
		//	if leaf print right
		else{
			if (!isdigit(node->right->value[0])){
				int sum1 = 0;
				for (int j = 0; j < node->right->value.size(); j++){
					sum1 += node->right->value[j];
				}
				f << "L:" + convertToASCII(node->right->value) + " ";
			}
		}
	}
}

void huffTree::createHeap(){
	int length = 0;
	while (hArray[length] != NULL){
		length++;
	}
	//order the hArray based on the frequency with selection sort
	int first;
	hNode *temp;
	for (int i = length - 1; i > 0; i--){
		first = 0;
		for (int j = 1; j <= i; j++){
			if (hArray[j]->frequency >= hArray[first]->frequency){
				first = j;
			}
		}
		temp = hArray[first];
		hArray[first] = hArray[i];
		hArray[i] = temp;
	}

	//merging the leaf nodes that create the heap
	while (hArray[1] != NULL){
		merge(0,1);
	}
	top = hArray[0];

}

void huffTree::merge(int vertex1, int vertex2){
	
	//the new node that the two nodes create
	hNode *nNode = new hNode;
	//hNode *node1 = hArray[vertex1];
	//hNode *node2 = hArray[vertex2];

	nNode->value = to_string(randomIntCount);
	randomIntCount++;
	nNode->frequency = hArray[vertex1]->frequency + hArray[vertex2]->frequency;
	nNode->left = hArray[vertex1];
	nNode->right = hArray[vertex2];

	//insert node in proper position
	

	hNode **tempArr = new hNode*[1000];
	//copy the array
	for (int i = 2; i < 1000; i++){
		hNode *tempNode = hArray[i];
		tempArr[i-2] = tempNode;
	}

	for (int k = 0; k < 1000; k++){
		hArray[k] = NULL;
	}

	//find the correct position for the new node
	tempArr[999] = NULL;
	tempArr[1000] = NULL;
	int count = 0;
	int newPos = 0;
	while (tempArr[count]!= NULL){
		if (nNode->frequency > tempArr[count]->frequency) {
			newPos++;
		}
		count++;
	}
	
	int count1 = 0;
	while (tempArr[count1] != NULL){
		count1++;
	}

	//inserts the new node into the array and 'forgets' the two it combined
	for (int j = 0; j < count1 + 1; j++){
		if (j > newPos){
			hArray[j] = tempArr[j-1];
		}
		else if (j == newPos){
			hArray[j] = nNode;
		}
		else{
			hArray[j] = tempArr[j];
		}
	}
}

void huffTree::insertChar(char nChar, int nFrequency){
	//create a new node and insert it into the huffman tree
	int length = 0;
	while (hArray[length] != NULL){
		length++;
	}
	hNode *nNode = new hNode;
	nNode->frequency = nFrequency;
	nNode->value = nChar;
	hArray[length] = nNode;
}

string huffTree::convertToASCII(string text){
	int sum = 0;
	for (unsigned int i = 0; i < text.size(); i++) {
		sum += text[i];
	}

	int lengthCount = 0;
	int temp = sum;
	while (temp)
	{
		temp = temp / 10;
		lengthCount++;
	}

	if (lengthCount == 2){
		string str = to_string(sum);
		str.insert(0, "0");
		return str;
	}
	else{
		return to_string(sum);
	}
}

string huffTree::convertFromASCII(string text){

	int sum = atoi(text.c_str());
	char ch = (char)sum;
	string str = "";
	str += ch;
	return str;
}
