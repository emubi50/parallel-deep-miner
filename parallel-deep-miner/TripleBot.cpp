#include "TripleBot.h"

TripleBot::TripleBot(bool isCpu) : BaseBot(isCpu)
{
}

TripleBot::~TripleBot()
{
}

void TripleBot::move(char c)
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

int TripleBot::mine(vector<int>* column)
{
	int score = 0;
	for (int i = 0; i < 3; i++)
	{
		if (column->empty()) throw std::logic_error("Column is actually empty! Column Size cannot be less than 0.");
		score += column->at(0);
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
