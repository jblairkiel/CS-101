#ifndef HUFFTREE_H_ 
#define HUFFTREE_H_

#include <string>

using namespace std;

struct hNode {
			string value;				//the value of the node
			int frequency;				//the frequency of the node
			hNode *left, *right;			//left and right pointers of a node
		};
class huffTree{

	private:
		hNode **hArray;					//array that holdes the leaf nodes that turns into a huffman tree
		hNode *top;					//the top of the huffman tree

		int encodingCounter;				//count of array
		string encodingTable[1000];			//table that holds the encoding of characters
		int encodingLength;				//length of the encoding table
		int randomIntCount;				//the random integer count for the internal nodes
		int lenOfArray;					//length of hArray 
		//int tempLength;				//the length of the temp array while being built (DECODE)
		int tempCount;					//the current position (DECODE)
		int decodeCount;				//the position of the Code (DECODE)
		string tFile;					//the name of the input tree file
		string cFile;					//the name of the input code file
		string convertToASCII(string text);
		string convertFromASCII(string text);
		
	public:
		huffTree(char charAr[1000]);
		huffTree(string treeFile, string codeFile);
		void createHeap();
		void insertChar(char nChar, int frequency);
		void merge(int vertex1, int vertex2);
		void printTraversals();
		void preorder(hNode* node, ofstream &f);
		void inorder(hNode* node, ofstream &f);
		void createEncodingTable();
		void encode(hNode* node, string code);
		void printEncodingLength();
		void printOriginalText(char charAr[1000]);
		void printBinary(char charAr[1000]);
		void constructTree();
		void decodeTraverse(hNode *node, string text);
		hNode* buildTree(hNode* node, string temp[]);
		void decode();

};
#endif
