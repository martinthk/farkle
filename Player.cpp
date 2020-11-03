#include "Player.h"

Player::Player()
{
}

Player::Player(std::string newName) {
	name = newName;
	score = 0;
}

// Show name
std::string Player::getName()
{
	return name;
}

// Add Score
void Player::addScore(int value)
{
	score += value;
}

// Show score
int Player::getScore()
{
	return score;
}


