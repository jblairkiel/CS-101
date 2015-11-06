#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <string>
#include "Hashtable.h"
#include "Tweet.h"
#include "MainMenu.h"

using namespace std;
/*! \file */
/** @brief The main function that runs the program.
	@param argc The number of arguments passed to the command line.
	@param argv[] The array of the arguments passed to the command line.
*/
int main(int argc, char* argv[]){

	// Open file from command line
	cout << "Reading in tweets:";
	ifstream input;
	string line;
	string creationDate;
	string tweetText;
	string screenName;
	Hashtable hTable = Hashtable(6000);
	//input.open(argv[2]);
	input.open("tweets.txt");
	if (input.is_open()){

		// while more lines exist
		while (getline(input, line)){

			// if "{"
			if (line.find('{') == 0){

				// begin new tweet

			}
			else{
				// parse
				string type;
				int pointLen = line.length();
				int point = 1;
				if (line[0] == '\"'){
					while (line[point] != '\"'){
						type += line[point];
						point++;
					}
				}

				// if "created_at"
				if (type == "created_at"){
					point = point + 3;
					while (point != pointLen-3){
						creationDate += line[point];
						point++;
					}
				}
				// elseif "text"
				else if (type == "text"){
					point = point + 3;
					while (point != pointLen-2){
						tweetText += line[point];
						point++;
					}
				}
				// elseif "screen_name"
				else if (type == "screen_name"){
					point = point + 3;
					while (point != pointLen-3){
						screenName += line[point];
						point++;
					}
					hTable.put(creationDate, tweetText, screenName);
					creationDate = "";
					tweetText = "";
					screenName = "";
				}
			}
		}
	}
	// Create Menu
	MainMenu menu = MainMenu();
	// while Menu is true
	int choice;
	while (menu.isActive())
	{
chooseAgain:
		menu.printMenu();
		cin >> choice;
		if (!cin){
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "\nInvalid Choice\n";
			goto chooseAgain;
		}
		else if (choice != 1 && choice != 2 && choice != 3 && choice != 4){
			cout << "\nInvalid Choice\n";
			goto chooseAgain;
		}
		
		// if (1) add a new treat
		if (choice == 1){
			creationDate = hTable.getCurrentTime();
			cout << "What is the tweet text (144 chars or less)?";
			char tweetTextChar[144];
			cin.ignore();
			cin.getline(tweetTextChar, 144);
			cout << "What is the screen name?";
			cin >> screenName;
			//create new tweet based off of inputs
			hTable.put(creationDate, string(tweetTextChar), screenName);
		}
		// elseif (2) delete tweets of a user
		else if (choice == 2){
			cout << "What is the screenname whose tweets you wish to delete?\n";
			cin >> screenName;
			hTable.remove(screenName);
		}
		// elseif (3) view all tweets of a user
		else if (choice == 3){
			cout << "What is the screen name of the tweets you wish to view?\n";
			cin >> screenName;
			cout << "\n";
			if (hTable.contains(screenName)){
				hTable.printTweets(screenName);
			}
			else{
				cout << "There are no tweets of the screenname \"" << screenName<<"\"";
			}
		}
		// elseif (4) quit the menu and the program
		else if (choice == 4){
			menu.setActive(false);
		}
	// end the program
	}
	return 0;

}