#pragma once
#include <vector>
#include <iostream>
using std::vector;

struct Position
{
	int x;
	int y;
} typedef pos;

class BaseBot
{
public:
	BaseBot(bool isCpu);
	~BaseBot();
	void move(int x, int y); // Move the bot to a new position
	virtual int mine(vector<int>* column) = 0; // Mine at the current position
	std::string getName();
	pos getPos();
	int getScore();
	void updateScore(int score);
	bool isCpu;
private:
	std::string name;
	pos position;
	int score;
};