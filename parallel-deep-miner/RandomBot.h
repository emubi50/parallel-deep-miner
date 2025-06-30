#pragma once
#include "BaseBot.h"
class RandomBot :
	public BaseBot
{
public:
	RandomBot(bool isCpu);
	~RandomBot();
	void move(char c); // Move the bot to a new position
	int mine(vector<int>* column) override; // Mine at the current position
	bool isCpu;
private:
	Position pos;
	int score;
};

