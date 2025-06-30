#include "BaseBot.h"

BaseBot::BaseBot(bool isCpu)
{
	position = { rand() % 5, rand() % 5 }; // Random initial position
	this->isCpu = isCpu;
	if (isCpu)
	{
		std::string cpuNames[] = {
			"CoreDigger",
			"MineRoid",
			"GeoTron",
			"SubLayer",
			"AX-500",
			"Excavatrix",
			"TerraBot",
			"Fossor-9",
			"Stratum",
			"Mineralis",
			"VoidReaper",
			"DepthClaw",
			"OreHunter",
			"DigCrusher",
			"GreedCore",
			"RoboMole",
			"DigiDig",
			"Z-Bot",
			"Chompy",
			"PickleTron"
		};
		name = cpuNames[rand() % (sizeof(cpuNames) / sizeof(cpuNames[0]))];
	}
	else
	{
		std::cout << "Enter name of your bot: ";
		std::cin >> name;
		std::cout << "Player Bot name: " << name << "\n";
	}
	score = 0; // Initialize score
}
BaseBot::~BaseBot()
{
}
void BaseBot::move(char c)
{
	Position movePos;
	switch (c)
	{
	case 'w':
		position.y > 0 ?
			movePos = { 0, -1 } :
			throw std::out_of_range("Move out of bounds! Position remains unchanged.");
		break;
	case 's':
		position.y < 4 ?
			movePos = { 0, 1 } :
			throw std::out_of_range("Move out of bounds! Position remains unchanged.");
		break;
	case 'a':
		position.x > 0 ?
			movePos = { -1, 0 } :
			throw std::out_of_range("Move out of bounds! Position remains unchanged.");
		break;
	case 'd':
		position.x < 4 ?
			movePos = { 1, 0 } :
			throw std::out_of_range("Move out of bounds! Position remains unchanged.");
		break;
	default:
		throw std::invalid_argument("Invalid Move Input! (Must be WASD)");
	}
	position += movePos;
}
int BaseBot::mine(vector<int>* column)
{
	// Implement mining logic in the derived class
	return 0; // Placeholder return value
}

std::string BaseBot::getName()
{
	return name;
}

Position BaseBot::getPos()
{
	return position;
}

int BaseBot::getScore()
{
	return score;
}

void BaseBot::updateScore(int score)
{
	this->score += score;
}