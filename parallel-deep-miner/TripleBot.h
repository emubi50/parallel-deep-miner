#pragma once
#include "BaseBot.h"
class TripleBot :
	public BaseBot
{
public:
	TripleBot(bool isCpu);
	~TripleBot();
	void move(char c); // Move the bot to a new position
	int mine(vector<int>* column) override; // Mine at the current position
	bool isCpu;
private:
	Position pos;
	int score;
};

