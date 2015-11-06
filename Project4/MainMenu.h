#ifndef MAINMENU_H_
#define MAINMENU_H_

#include <string>
#include <iostream>
#include "Tweet.h"

using namespace std;
/** @brief Class for the Main Menu options.
*/
class MainMenu {

	private:

	bool active;

	public:
	MainMenu();
	bool isActive();
	void setActive(bool cond);
	void printMenu();
		
};

/** @brief Constructor for MainMenu
*/
MainMenu::MainMenu(){
	active = true;
	}

/** @brief Returns the state of the MainMenu.
*/
bool MainMenu::isActive(){
	return active;
}

/** @brief Sets the State of the MainMenu.
*/
void MainMenu::setActive(bool cond){
	active = cond;
}

/** @brief Prints out the options for the menu.
*/
void MainMenu::printMenu(){
	cout << "\n1. Enter new Tweet\n";
	cout << "2. Delete all tweets for a given screen_name\n";
	cout << "3. View Tweets\n";
	cout << "4. Quit\n";
}

#endif