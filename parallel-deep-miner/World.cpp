#include "World.h"

World::World()
{
	// Initialize the world with random values
	generateWorld();
	roundCounter = 0;
	int gameMode = 0;
	while (gameMode != 1 && gameMode != 2)
	{
		std::cout << "Select game mode (player vs cpu - 1 / cpu vs cpu - 2): ";
		std::cin >> gameMode;
		std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
	}
	addBot(--gameMode);
}
World::~World()
{
}
bool World::displayWorld()
{
	//check if the world still has something to mine
	int emptyColumns = 0;

	// Display the world
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i < world.size(); ++i)
	{
		for (int j = 0; j < world[i].size(); ++j)
		{
			int color = 0;
			switch (world.at(i).at(j).size())
			{
			case 1:
				color = (world[i][j][0] == 0) ? 8 : 5;
				break;
			case 2:
				color = 13; // BRIGHT MAGENTA
				break;
			case 3:
				color = 4; // RED
				break;
			case 4:
				color = 12; // BRIGHT RED
				break;
			case 5:
				color = 6; // YELLOW
				break;
			case 6:
				color = 14; // BRIGHT YELLOW
				break;
			case 7:
				color = 2; // GREEN
				break;
			case 8:
				color = 10; // BRIGHT GREEN
				break;
			case 9:
				color = 3; // CYAN
				break;
			case 10:
				color = 11; //BRIGHT CYAN
				break;
			}

			int currentColumnValue = world[i][j][0];
			if (currentColumnValue == 0)
			{
				emptyColumns++;
			}
			SetConsoleTextAttribute(hConsole, color); // Set color based on column size
			std::cout << currentColumnValue << " ";
			SetConsoleTextAttribute(hConsole, 7); // Reset to white
		}
		std::cout << std::endl;
	}

	return (emptyColumns != 25);
}
void World::addBot(bool isCpu)
{
	int choice = 0;

	while (bots.size() < 2)
	{
		if (isCpu == false)
		{
			std::cout << "Bot types (SortBot - 1 / TripleBot - 2 / RandomBot - 3): ";
			std::cin >> choice;
			std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
		}
		else
		{
			choice = rand() % 3 + 1;
		}
		switch (choice)
		{
		case 1:
			bots.push_back(new SortBot(isCpu)); // Add a SortBot
			std::cout << "Sortbot added! CPU? " << isCpu << "\n";
			break;
		case 2:
			bots.push_back(new TripleBot(isCpu)); // Add a TripleBot
			std::cout << "TripleBot added! CPU? " << isCpu << "\n";
			break;
		case 3:
			bots.push_back(new RandomBot(isCpu)); // Add a RandomBot
			std::cout << "RandomBot added! CPU? " << isCpu << "\n";
			break;
		default:
			std::cout << "Invalid Input!\n";
			continue;
		}
		isCpu = true;
	}
	startRound(rand() % 2, 0); // Randomly select the first bot to start
}
void World::moveBot(BaseBot* currentBot)
{
	int x = currentBot->getPos().x;
	int y = currentBot->getPos().y;
	// Move the bot in the world, but Bot updates its own position
	if (currentBot->isCpu == false)
	{
		std::cout << "Enter new position: \n";
		std::cout << "Enter x (0-4): ";
		while (!(std::cin >> x) || x < 0 || x > 4)
		{
			std::cout << "Invalid input! Enter x (0-4): ";
			std::cin.clear();
			std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
		}
		std::cout << "Enter y (0-4): ";
		while (!(std::cin >> y) || y < 0 || y > 4)
		{
			std::cout << "Invalid input! Enter y (0-4): ";
			std::cin.clear();
			std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
		}
	}
	else
	{
		std::cout << currentBot->getName() << " is moving...\n";
		x = rand() % 5;
		y = rand() % 5;
	}
	currentBot->move(x, y); // Move the bot to the new position
	std::cout << currentBot->getName() << " moved to (" << x << ", " << y << ")\n";
}
void World::generateWorld()
{
	for (int i = 0; i < 5; i++)
	{
		vector<vector<int>> row;
		for (int j = 0; j < 5; j++)
		{
			vector<int> column;
			for (int k = 0; k < 10; k++)
			{
				column.push_back(rand() % 9 + 1); // Random value between 1 and 9
			}
			row.push_back(column);
		}
		world.push_back(row);
	}
}

void World::newWorldOrder()
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			switch (rand() % 3)
			{
			case 0:
				std::random_shuffle(world[i][j].begin(), world[i][j].end()); // Shuffle the column
				break;
			case 1:
				std::sort(world[i][j].begin(), world[i][j].end()); // Sort in ascending order
				break;
			case 2:
				std::sort(world[i][j].begin(), world[i][j].end(), std::greater<int>()); // Sort in descending order
				break;
			}
		}
	}
}

void World::startRound(int firstBot, int totalScore)
{
	//display the world
	if (!displayWorld())
	{
		// ISSUE: ENTER KEY MAY NEED TO BE PRESSED TWICE TO CLOSE THE PROGRAM
		std::cout << "Game Over! Press ENTER to close the program.";
		do {
			std::cin.clear();
			std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
		} while (std::cin.get() != '\n');
		return;
	}
	std::cout << "========================\n";

	// Start the round  
	roundCounter++;
	std::cout << "Round " << roundCounter << ":\n";
	for (auto& bot : bots)
	{
		moveBot(bot);
		// Check if the bot's position is within bounds before mining  
		int x = bot->getPos().x;
		int y = bot->getPos().y;
		if (x >= 0 && x < world.size() && y >= 0 && y < world[x].size())
		{
			int scoreIncrement = bot->mine(&world[x][y]); // Mine at the current position
			bot->updateScore(scoreIncrement);
			totalScore += scoreIncrement;
		}
		else
		{
			std::cout << "Bot position out of bounds! Skipping mining.\n";
		}
	}
	if (totalScore % 50 != totalScore)
	{
		std::cout << "========================\n";
		std::cout << "50 Points reached! Creating NEW WORLD ORDER...\n";
		std::cout << "========================\n";
		newWorldOrder(); // Shuffle the world
		totalScore %= 50; // Reset the score
	}
	startRound(firstBot, totalScore);
}