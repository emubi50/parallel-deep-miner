#pragma once
#include <vector>
#include <iostream>
#include <algorithm>
#include <windows.h>
#include "BaseBot.h"
#include "SortBot.h"
#include "TripleBot.h"
#include "RandomBot.h"
using std::vector;

class World
{
public:
	World();
	~World();
	bool displayWorld();
	void addBot(bool gameMode);
	void moveBot(BaseBot* currentBot); // Move the bot in the world, but Bot updates its own position
	void startRound(int firstBot, int totalScore);
private:
	void generateWorld();
	vector<vector<vector<int>>> world; //5 x 5 x 10 world
	vector<BaseBot*> bots; // List of bots in the world (limited to 2 bots for now)
	int roundCounter;
};

