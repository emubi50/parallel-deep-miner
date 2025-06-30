#include "RandomBot.h"

RandomBot::RandomBot(bool isCpu) : BaseBot(isCpu)
{
}

RandomBot::~RandomBot()
{
}

void RandomBot::move(char c)
{
	try
	{
		BaseBot::move(c);
	}
	catch (const std::out_of_range& except)
	{
		throw;
	}
	catch (const std::invalid_argument& except)
	{
		throw;
	}
}

int RandomBot::mine(vector<int>* column)
{
	int score = 0;
	for (int i = 0; i < 2; i++)
	{
		if (column->empty()) throw std::logic_error("Column is actually empty! Column Size cannot be less than 0.");
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
