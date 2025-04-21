#include "TripleBot.h"

TripleBot::TripleBot(bool isCpu) : BaseBot(isCpu)
{
}

TripleBot::~TripleBot()
{
}

void TripleBot::move(int x, int y)
{
	BaseBot::move(x, y);
}

int TripleBot::mine(vector<int>* column)
{
	int score = 0;
	for (int i = 0; i < 3; i++)
	{
		score += column->at(0);
		if (column->empty())
		{
			break;
		}
		if (column->size() == 1)
		{
			column->back() = 0; // Set the value to 0
		}
		else
		{
			column->erase(column->begin());
		}
	}
	return score;
}
