#ifndef PLAYER_H
#define PLAYER_H

#include <string>


class Player {
private:
	std::string name;
	int score;

public:
	Player();
	Player(std::string); // New player constructor

	std::string getName(); // show Name

	void addScore(int); // add to score
	int getScore(); // show score	
};
#endif // !PLAYER_H
