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
void BaseBot::move(int x, int y)
{
	position = { x, y };
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

pos BaseBot::getPos()
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