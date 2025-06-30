#include "SortBot.h"

SortBot::SortBot(bool isCpu) : BaseBot(isCpu)
{
}

SortBot::~SortBot()
{
}

void SortBot::move(char c)
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

int SortBot::mine(vector<int>* column)
{
	int score = 0;
	if (column->empty()) throw std::logic_error("Column is actually empty! Column Size cannot be less than 0.");
	//sort column in descending order: begins with highest value
	std::sort(column->begin(), column->end(), std::greater<int>());
	score += column->at(0); // Add the highest value to the score
	if (column->size() == 1)
	{
		column->back() = 0; // Set the value to 0
	}
	else
	{
		column->erase(column->begin()); // Remove the highest value
	}
	return score;
}