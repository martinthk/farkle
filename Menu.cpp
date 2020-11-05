#include "Menu.h"

// Template: Main Menu
void Menu::showMenu()
{
	system("cls");	// Clear screen
	std::cout << "=================" << std::endl;
	std::cout << "Welcome to Farkle" << std::endl;
	std::cout << "=================" << std::endl;
	std::cout << std::endl << std::endl;

	std::cout << "[1] New Game" << std::endl;
	std::cout << "[2] Show Rules" << std::endl;
	std::cout << "[3] Quit" << std::endl << std::endl;

	std::cout << "Please enter a selection: ";
}

// Function: Reads the Rules from a .txt file
void Menu::showRules()
{
	std::string line;	// holds each line in the file
	std::string filename = "Rules.txt";	// the file to be opened
	std::ifstream myfile(filename);	// opens a stream of the file

	if (myfile.is_open())
	{
		system("cls"); // clear screen

		// Get and output all lines in the file
		while (getline(myfile, line))
		{
			std::cout << line << std::endl;
		}

		myfile.close();	// close the file
	}
	else
	{
		std::cout << "Unable to open '" << filename << "'" << std::endl;
	}

	std::cout << std::endl;
	system("pause");	// Wait for player to press enter
}
