#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Menu.h"
#include "Player.h"

#include <iostream>
#include <string>
#include <time.h>
#include <vector>

class Game
{
private:
	// Inputs
	int getInput();

	// Print
	void showRoll();
	void showKept();
	void congratulate(Player);
	void finalRound(Player);
	void welcome();

	// Setup
	void askPlayersNum();
	void setupPlayerNames();
	void askTargetScore();
	void askMiniPoints();

	// Play
	void generateDice();
	void rollDice();
	void reRoll();
	void countDice();

	// Checking
	bool checkForWinner(int);
	bool checkIsVaild(int);
	bool checkScoringDice();
	bool checkPairs();

	void selection(std::string);
	void scoring();
	void scoring2();
	Player getWinner();

	//	Data member
	int targetScore;
	int miniPoints;
	int numOfPlayers;
	int counter[6];
	int keptDices[6];
	int playerTurn;
	int turnScore;
	int winnerTurn;
	bool bfarkle;
	bool win;
	std::vector <Player> players;
	std::vector <int> dices;
	int move;
	std::string choice;
	Player winner;

	// Main functions
	void turn(); 
	Player play();

	

public:
	void gameLoop();

};

#endif // !GAME_H
