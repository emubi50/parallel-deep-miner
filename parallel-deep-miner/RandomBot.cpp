#include "RandomBot.h"

RandomBot::RandomBot(bool isCpu) : BaseBot(isCpu)
{
}

RandomBot::~RandomBot()
{
}

void RandomBot::move(int x, int y)
{
	BaseBot::move(x, y);
}

int RandomBot::mine(vector<int>* column)
{
	int score = 0;
	for (int i = 0; i < 2; i++)
	{
		int randomIndex = rand() % column->size();
		score += column->at(randomIndex);
		if (column->size() == 1)
		{
			column->back() = 0;
		}
		else
		{
			column->erase(column->begin() + randomIndex);
		}
	}
	return score;
}
