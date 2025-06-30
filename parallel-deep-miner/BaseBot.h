#pragma once
#include <vector>
#include <iostream>
#include "Position.h"

using std::vector;

class BaseBot
{
public:
	BaseBot(bool isCpu);
	~BaseBot();
	void move(char c); // Move the bot to a new position
	virtual int mine(vector<int>* column) = 0; // Mine at the current position
	std::string getName();
	Position getPos();
	int getScore();
	void updateScore(int score);
	bool isCpu;
private:
	std::string name;
	Position position;
	int score;
};