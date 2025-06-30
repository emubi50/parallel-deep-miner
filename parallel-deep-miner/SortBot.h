#pragma once
#include "BaseBot.h"
#include <algorithm>
class SortBot :
	public BaseBot
{
public:
	SortBot(bool isCpu);
	~SortBot();
	void move(char c); // Move the bot to a new position
	int mine(vector<int>* column) override; // Mine at the current position
	bool isCpu;
private:
	Position pos;
	int score;
};

