#include "SortBot.h"

SortBot::SortBot(bool isCpu) : BaseBot(isCpu)
{
}

SortBot::~SortBot()
{
}

void SortBot::move(int x, int y)
{
	BaseBot::move(x, y);
}

int SortBot::mine(vector<int>* column)
{
	int score = 0;
	//sort column in descending order: begins with highest value
	std::sort(column->begin(), column->end(), std::greater<int>());
	score += column->at(0); // Add the highest value to the score
	if (column->size() > 1)
	{
		column->erase(column->begin()); // Remove the highest value
	}
	else
	{
		column->back() = 0; // Set the value to 0
	}
	return score;
}