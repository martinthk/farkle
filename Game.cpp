#include "Game.h"

//----------------------- Inputs -----------------------
int Game::getInput() 
{
	unsigned int selection;

	while (!(std::cin >> selection)) {
		std::cout << "Invalid selection. Try again: ";
	}
	return selection;
}
//------------------------------------------------------


//----------------------- Print -----------------------
// Fuction: Print rolled dices
void Game::showRoll()
{
	std::cout << "\n\t";
	for (int i = 0; i < dices.size(); i++) {
		if (dices[i] == NULL) {
			std::cout << "[x]" << "   ";
		}
		else {
			std::cout << "[" << dices[i] << "]" << "   ";
		}
	}
	std::cout << std::endl;
	//showKept();
}

// For testing purpose only
void Game::showKept() 
{
	for (int i = 0; i < 6; i++) {
		std::cout << i + 1 << ": " << keptDices[i] << "   ";
	}
}

// Template: Announcing the winner
void Game::congratulate(Player player)
{
	system("cls");
	std::cout << "*****************" << std::endl;
	std::cout << "CONGRATULATIONS" << std::endl;
	std::cout << "*****************" << std::endl;
	std::cout << player.getName() << " is the winner with a score of " << player.getScore() << "!" << std::endl << std::endl;

	system("pause");
}

// Template: Announcing final round has begun
void Game::finalRound(Player player)
{
	{
		system("cls");
		std::cout << "=================" << std::endl;
		std::cout << "FINAL ROUND" << std::endl;
		std::cout << "=================" << std::endl;
		std::cout << player.getName() << " has a score of " << player.getScore() << "!" << std::endl;
		std::cout << "The final round of play has begun! Good luck!" << std::endl << std::endl;

		system("pause");
	}
}

void Game::welcome(){
	std::string playerNames;

	system("cls");
	std:: cout << "=================" << std::endl;
	std::cout << "WELCOME TO FARKLE" << std::endl;
	std::cout << "=================" << std::endl;
	for (int i = 0; i < players.size(); i++)
	{
		if (i == players.size() - 1)
		{
			playerNames += "and " + players[i].getName();
		}
		else
		{
			playerNames += players[i].getName() + ", ";
		}
	}

	std::cout << "Welcome " << playerNames << "!" << std::endl << std::endl;

	system("pause"); // Wait for player to press enter

}
//------------------------------------------------------


//----------------------- Setup -----------------------
// Template: Asking Number of Players
void Game::askPlayersNum()
{
	system("cls");
	std::cout << "=================" << std::endl;
	std::cout << "NEW GAME" << std::endl;
	std::cout << "=================" << std::endl;
	std::cout << "How many players are there? ";
}

// Fuctions: Setup player names
void Game::setupPlayerNames()
{
	system("cls");
	std::cout << "=================" << std::endl;
	std::cout << "SETUP PLAYER NAMES" << std::endl;
	std::cout << "=================" << std::endl;

	// Get the name for each player in the players vector
	for (unsigned int i = 0; i < numOfPlayers; i++)
	{
		std::string name;
		std::cout << "Enter name for Player " << (i + 1) << " : ";
		std::cin >> name;


		// create a new player object in the player vector using the name provided
		players.push_back(Player(name));
	}
}


// Template: Asking target score
void Game::askTargetScore()
{
	std::cout << "=================" << std::endl;
	std::cout << "TARGET SCORE" << std::endl;
	std::cout << "=================" << std::endl;

	// Let user to choose the target score
	std::cout << "Choose the target score for the game: \n\n\t[1] 5,000  [2] 10,000  [3] 15,000 ";
}

// Template: Asking mini points required to roll before saving points
void Game::askMiniPoints()
{
	std::cout << "=================" << std::endl;
	std::cout << "MINIMUM POINTS" << std::endl;
	std::cout << "=================" << std::endl;

	std::cout << "Enter the minimum points required to roll before saving points: \n\n\t[1] 350 [2] 500 [3] 750 [4] 1000 ";
}
//------------------------------------------------------


//----------------------- Play -----------------------
void Game::generateDice()
{
	srand(time(NULL));
	for (int i = 0; i < 6; i++) {
			dices.push_back(rand() % 6 + 1); // Creates a random number from 1 to 6
	}
}

void Game::rollDice()
{
	srand(time(NULL));
	for (int i = 0; i < 6; i++) {
		dices[i] = rand() % 6 + 1; // Creates a random number from 1 to 6
	}
}

void Game::reRoll() {
	srand(time(NULL));
	for (int i = 0; i < 6; i++) {
		if (dices[i] != NULL){
			dices[i] = rand() % 6 + 1;
		}
	}
}

// Function: Count for the dice value
void Game::countDice()
{
	// Initailize the vlaue inside array to 0
	for (int i = 0; i < dices.size(); i++) {
		counter[i] = 0;
	}

	// Count each dice value and store the value into the counting array
	for (int i = 0; i < dices.size(); i++) {
		if (dices[i] != NULL) {
			counter[dices[i] - 1] += 1;
		}
	}

}
//------------------------------------------------------


//----------------------- Checking -----------------------
// Function: Checks if the player has exceed the target score
bool Game::checkForWinner(int pScore)
{ 
	win = pScore >= targetScore;
	return win;
} 

// Function: Checks if the user's selection is a valid input
bool Game::checkIsVaild(int selection)
{
	if (selection == 0 || selection == 9 || selection == 8 || selection == 7) {
		return false;
	}
	else if (selection > 0 && selection <= 123456)
	{
		return true;
	}
	return false;
}

// Function: Checks for any 1's/ 5's/ 3 of a kind  
bool Game::checkScoringDice()
{
	// counter[0] is number of 1's, counter[4] is number of 5's
	if (counter[0] >= 1 || counter[4] >= 1)
	{
		return true;
	}

	// If no 1 or 5, check for any triples
	for (int i = 1; i < 6 ; i++)
	{
		// Skip 5
		if (i == 4) {
			i = 5;
		}

		if (counter[i] >= 3)
		{
			return true; 
		}
	}

	// No scoring dice
	return false;
}

// Function: Checks if the keptDices has 3 pairs
// **Return T if there is 3 pairs
// **Return F if there is no 3 pairs
bool Game::checkPairs()
{
	int pair = 0;
	for (int i = 0; i < 6; i++) {
		if (keptDices[i] == 2) {
			pair++;
		}
	}
	return (pair == 3);
}
//------------------------------------------------------



// Function: Process the selection
// **Add to the keptDices & change to NULL
void Game::selection(std::string newSelection)
{
	char temp0 = newSelection[0];
	if (!(temp0 == '9' || temp0 == '0')) {
		for (int i = 0; i < newSelection.length(); i++) {
			char select = newSelection[i];
				int temp1 = select - '0';
				int index = temp1 - 1;
				int diceValue = dices[index];
				keptDices[diceValue - 1] ++;
				dices[index] = NULL;
		}
	}
}

// Function: base scoring function
void Game::scoring()
{
	// 1
	if (keptDices[0] >= 1) {
		while (keptDices[0] != 0) {
			if (keptDices[0] >= 3) {
				turnScore += 1000; // 3 x 1's
				keptDices[0] -= 3;
			}
			else if (keptDices[0] >= 1) {
				turnScore += 100 * keptDices[0]; //1's
				keptDices[0] -= keptDices[0];
			}
		}
	}

	// 5
	if (keptDices[4] >= 1) {
		while (keptDices[4] != 0) {
			if (keptDices[4] >= 3) {
				turnScore += 500; // 3 x 1's
				keptDices[4] -= 3;
			}
			else if (keptDices[4] >= 1) {
				turnScore += 50 * keptDices[4]; //1's
				keptDices[4] -= keptDices[4];
			}
		}
	}

	// 2
	if (keptDices[1] >= 3) {
		while (keptDices[1] != 0 && keptDices[1] >= 3) {
			turnScore += 200;
			keptDices[1] -= 3;
		}
	}

	// 3
	if (keptDices[2] >= 3) {
		while (keptDices[2] != 0 && keptDices[2] >= 3) {
			turnScore += 300;
			keptDices[2] -= 3;
		}
	}

	// 4
	if (keptDices[3] >= 3) {
		while (keptDices[3] != 0 && keptDices[3] >= 3) {
			turnScore += 400;
			keptDices[3] -= 3;
		}
	}

	// 6
	if (keptDices[5] >= 3) {
		while (keptDices[5] != 0 && keptDices[5] >= 3) {
			turnScore += 600;
			keptDices[5] -= 3;
		}
	}
}

void Game::scoring2()
{
	// Straight
	if (keptDices[0] == 1 && keptDices[1] == 1 && keptDices[2] == 1 && keptDices[3] == 1 && keptDices[4] == 1 && keptDices[5] == 1) {
		turnScore += 1500;
		for (int i = 0; i < 6; i++) {
			keptDices[i] = 0;
		}
	}

	//6-of-a-kind *instant win
	if (keptDices[0] == 6 || keptDices[1] == 6 || keptDices[2] == 6 || keptDices[3] == 6 || keptDices[4] == 6 || keptDices[5] == 6) {
		turnScore = 9999;
	}

	//3 pairs
	if (checkPairs()) {
		turnScore = 1000;
		for (int i = 0; i < 6; i++) {
			keptDices[i] = 0;
		}
	}
}
//------------------------------------------------------



Player Game::getWinner()
{
	for (int i = 1; i < players.size(); i++)
	{
		if (players[i].getScore() > players[i - 1].getScore())
		{
			winner = players[i];
		}
	}

	return winner;
}


void Game::turn()
{
	turnScore = 0;
	bfarkle = false;
	bool hasPassed = false;
	bool canSave = false;
	int cTemp = 0;
	while (!hasPassed) {


		do {
			std::cout << "\n\nEnter [8] to quit, [9] to roll dice or [0] to score the points and end your turn." << std::endl;
			std::cout << "\n\tMove: ";
			std::cin >> move;

			// Vaildation
			while (!(move == 8 || move == 9 || move == 0)) {
				std::cout << "Invalid move. Try again: ";
				std::cin >> move;
			}
				switch (move)
				{
				case 9:
					reRoll();
					showRoll();
					countDice();
					if (!checkScoringDice()) {
						bfarkle = true;
						hasPassed = true;
						turnScore = 0;
					}
					else {
						std::cout << "\n\nThe dice you want are? #[1~6] " << std::endl;
						std::cout << "\n\tSelection: ";
						std::cin >> choice;
						cTemp = std::stoi(choice); // Convert string to int
						while (!checkIsVaild(cTemp)) {
							std::cout << "Invalid selection. Try again: ";
							std::cin >> choice;
							cTemp = std::stoi(choice);
						}
						selection(choice);
						showRoll();
					}
					break;
				case 0:
					scoring2();
					scoring();

					// add turnscore to players score if it has exceeded the miniPoints
					if (turnScore > miniPoints)
					{
						players[playerTurn].addScore(turnScore);
						hasPassed = true;
					}
					else {
						std::cout << "\nYou have to roll at least " << miniPoints << " points before saving the points!!!" << std::endl;
					}
					break;
				case 8:
					exit(0);
					break;
				default:
					break;
				}

			if (dices[0] == NULL && dices[1] == NULL && dices[2] == NULL && dices[3] == NULL && dices[4] == NULL &&
				dices[5] == NULL) {
				scoring2();
				scoring();
				players[playerTurn].addScore(turnScore);
				hasPassed = true;
			}
			
		} while (!(hasPassed || bfarkle));
		

		if (bfarkle) {
			std::cout <<"\n\n\t" << players[playerTurn].getName() << " has FARKLED!" << std::endl;
			system("pause");
		}
		
		if(hasPassed && !bfarkle)
		{
			std::cout << "\n\n\t" << players[playerTurn].getName() << " has scored " << turnScore << " points this turn!" << std::endl;
		}

		if (hasPassed) {
			std::cout << "\n\t" << players[playerTurn].getName() << "'s TURN ENDS!" << std::endl;
			std::cout << std::endl;
			system("pause");
		}
	}
}

Player Game::play()
{
	numOfPlayers = 0; // Hold the number of players
	playerTurn = 0; // Keeps track of which players turn it is, based on vector index
	turnScore = 0;
	targetScore = 0;
	miniPoints = 0;

	askPlayersNum();

	// Vaildates player input is within 1-4
	while (!(numOfPlayers >= 1 && numOfPlayers <= 4))
	{
		numOfPlayers = getInput();
		playerTurn = rand() % numOfPlayers;

		if (numOfPlayers < 1 || numOfPlayers > 4)
		{
			std::cout << "Invalid number of players." << std::endl;
			std::cout << "Please try again: ";
		}
	}


	setupPlayerNames();
	welcome();


	// ======================== Extra Functionalilty========================
	// Note for quick testing Final Round: 
	// 1. Add a new targetScore condition in while loop (e.g. || targetScore == 50)
	// 2. Add a switch case for that (e.g. case 4: targetScore = 50;)
	// 3. Add another condition if the if statement ( e.g. || targetScore == 50)
	askTargetScore();
	while (!(targetScore == 5000 || targetScore == 10000 || targetScore == 15000 )) {
		targetScore = getInput();
		switch (targetScore) {
		case 1:
			targetScore = 5000;
			break;
		case 2:
			targetScore = 10000;
			break;
		case 3:
			targetScore = 15000;
			break;
		default:
			break;
		}
		if (!(targetScore == 5000 || targetScore == 10000 || targetScore == 15000 )) {
			std::cout << "Invalid! Must choose from the above options." << std::endl;
			std::cout << "Please try again: ";
		}
	}

	askMiniPoints();
	while (!(miniPoints == 350 || miniPoints == 500 || miniPoints == 750 || miniPoints == 1000)) {
		miniPoints = getInput();
		switch (miniPoints) {
		case 1:
			miniPoints = 350;
			break;
		case 2:
			miniPoints = 500;
			break;
		case 3:
			miniPoints = 750;
			break;
		case 4:
			miniPoints = 1000;
		default:
			break;
		}
		if (!(miniPoints == 350 || miniPoints == 500 || miniPoints == 750 || miniPoints == 1000)) {
			std::cout << "Invalid! Must choose from the above options." << std::endl;
			std::cout << "Please try again: ";
		}
	}
	// =====================================================================

	// Continue looping until a winner is declared
	while (winner.getName() == "")
	{
		// Return to first players turn if necessary
		if (playerTurn == players.size())
		{
			playerTurn = 0;
		}

		if (winner.getName() == "") {
			system("cls");
			std::cout << "\n**********************************************************" << std::endl;
			std::cout << "\tFARKLE :: A dice game for 1 -4 players" << std::endl;
			std::cout << "**********************************************************" << std::endl;
			for (int i = 0; i < players.size(); i++) {
				std::cout << players[i].getName() << "\tTotal: " << players[i].getScore() << std::endl;
			}
			std::cout << "\n**********************************************************" << std::endl;

			std::cout << players[playerTurn].getName() << "'s Turn!" << std::endl;

			// Initialize
			for (int i = 0; i < 6; i++) {
				keptDices[i] = 0;
			}

			rollDice();
			turn(); // Run normal player turn 
		}

		// Check if players score is over target score
		if (win == false) {
			if (checkForWinner(players[playerTurn].getScore())) {
				finalRound(players[playerTurn]);
				win = true;
				winnerTurn = playerTurn;
			}
		}


		// The game is over if all players have had a turn after a player reaches the target score 
		if (win == true && winnerTurn != playerTurn)
		{
			winner = getWinner();
		}

		playerTurn++;// Send to next players turn
	}
		return winner;
}


void Game::gameLoop()
{
	bool quit = false;
	unsigned int selection;
	Player winner;

	while (!quit)
	{
		Menu::showMenu();
		selection = getInput();

		switch (selection)
		{
		case 1:	// New Game
			generateDice();
			winner = play();
			congratulate(winner);
			break;
		case 2:	// Show Rules
			Menu::showRules();
			break;
		case 3:	// Quit
			quit = true;
			break;
		default: // Anything else
			break;
		}
	}
}
