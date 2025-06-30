#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "World.h"

TEST_CASE("SortBot Movement Tests", "[SortBot::SortBot][move]")
{
	srand(time(NULL));
	SortBot sortBot(true);
	Position startPos = sortBot.getPos();

	SECTION("SortBot Constructor")
	{
		REQUIRE(sortBot.getPos().x >= 0);
		REQUIRE(sortBot.getPos().x <= 4);
		REQUIRE(sortBot.getPos().y >= 0);
		REQUIRE(sortBot.getPos().y <= 4);
		REQUIRE(sortBot.getScore() == 0);
	}

	SECTION("SortBot Move Up")
	{
		for (int i = 0; i < 5; i++)
		{
			if (startPos.y == 0)
			{
				CHECK_THROWS_AS(sortBot.move('w'), std::out_of_range);
				REQUIRE(sortBot.getPos().y == startPos.y);
			}
			else
			{
				sortBot.move('w');
				REQUIRE(sortBot.getPos().y == startPos.y - 1);
			}
			REQUIRE(sortBot.getPos().x == startPos.x);
			REQUIRE(sortBot.getPos().x >= 0);
			REQUIRE(sortBot.getPos().x <= 4);
			REQUIRE(sortBot.getPos().y >= 0);
			REQUIRE(sortBot.getPos().y <= 4);
			startPos = sortBot.getPos();
		}
	}

	SECTION("SortBot Move Down")
	{
		for (int i = 0; i < 5; i++)
		{
			if (startPos.y == 4)
			{
				CHECK_THROWS_AS(sortBot.move('s'), std::out_of_range);
				REQUIRE(sortBot.getPos().y == startPos.y);
			}
			else
			{
				sortBot.move('s');
				REQUIRE(sortBot.getPos().y == startPos.y + 1);
			}
			REQUIRE(sortBot.getPos().x == startPos.x);
			REQUIRE(sortBot.getPos().x >= 0);
			REQUIRE(sortBot.getPos().x <= 4);
			REQUIRE(sortBot.getPos().y >= 0);
			REQUIRE(sortBot.getPos().y <= 4);
			startPos = sortBot.getPos();
		}
	}

	SECTION("SortBot Move Left")
	{
		for (int i = 0; i < 5; i++)
		{
			if (startPos.x == 0)
			{
				CHECK_THROWS_AS(sortBot.move('a'), std::out_of_range);
				REQUIRE(sortBot.getPos().x == startPos.x);
			}
			else
			{
				sortBot.move('a');
				REQUIRE(sortBot.getPos().x == startPos.x - 1);
			}
			REQUIRE(sortBot.getPos().y == startPos.y);
			REQUIRE(sortBot.getPos().x >= 0);
			REQUIRE(sortBot.getPos().x <= 4);
			REQUIRE(sortBot.getPos().y >= 0);
			REQUIRE(sortBot.getPos().y <= 4);
			startPos = sortBot.getPos();
		}
	}

	SECTION("SortBot Move Right")
	{
		for (int i = 0; i < 5; i++)
		{
			if (startPos.x == 4)
			{
				CHECK_THROWS_AS(sortBot.move('d'), std::out_of_range);
				REQUIRE(sortBot.getPos().x == startPos.x);
			}
			else
			{
				sortBot.move('d');
				REQUIRE(sortBot.getPos().x == startPos.x + 1);
			}
			REQUIRE(sortBot.getPos().y == startPos.y);
			REQUIRE(sortBot.getPos().x >= 0);
			REQUIRE(sortBot.getPos().x <= 4);
			REQUIRE(sortBot.getPos().y >= 0);
			REQUIRE(sortBot.getPos().y <= 4);
			startPos = sortBot.getPos();
		}		
	}

	SECTION("SortBot Invalid Moves")
	{
		CHECK_THROWS_AS(sortBot.move('N'), std::invalid_argument);
		CHECK_THROWS_AS(sortBot.move(' '), std::invalid_argument);
		CHECK_THROWS_AS(sortBot.move('1'), std::invalid_argument);
		CHECK_THROWS_AS(sortBot.move('!'), std::invalid_argument);
	}
}

TEST_CASE("SortBot Score Tests", "[SortBot::SortBot][score]")
{
	srand(time(NULL));
	SortBot sortBot(true);
	int score = 0;

	SECTION("SortBot Get Score")
	{
		REQUIRE(sortBot.getScore() == 0);
	}
	
	SECTION("SortBot Update Score")
	{
		score = rand() % 100 + 1;
		sortBot.updateScore(score);
		REQUIRE(sortBot.getScore() == score);
	}
}

TEST_CASE("SortBot Mining Tests", "[SortBot::SortBot][mine]")
{
	srand(time(NULL));
	SortBot sortBot(true);
	std::vector<int> column;
	int columnSize;
	int mineScore = 0;

	SECTION("SortBot Full Column Mine Once")
	{
		column = { 1, 2, 3, 8, 6, 8, 5, 1, 5, 6 };
		columnSize = column.size();
		REQUIRE(sortBot.getScore() == 0);
		mineScore = sortBot.mine(&column);
		columnSize--;
		for (int i = 0; i + 1 < columnSize; i++)
		{
			REQUIRE(column[i] >= column[i + 1]);
		}
		sortBot.updateScore(mineScore);
		REQUIRE(column.size() == columnSize);
		REQUIRE(sortBot.getScore() == mineScore);
	}

	SECTION("SortBot Three Values Left To Mine")
	{
		column = { 2, 1, 3 };
		columnSize = column.size();
		REQUIRE(sortBot.getScore() == 0);
		mineScore = sortBot.mine(&column);
		columnSize--;
		for (int i = 0; i + 1 < columnSize; i++)
		{
			REQUIRE(column[i] >= column[i + 1]);
		}
		sortBot.updateScore(mineScore);
		REQUIRE(column.size() == 2);
		REQUIRE(sortBot.getScore() == mineScore);
	}

	SECTION("TripleBot Two Values Left To Mine")
	{
		column = { 2, 1 };
		columnSize = column.size();
		REQUIRE(sortBot.getScore() == 0);
		mineScore = sortBot.mine(&column);
		columnSize--;
		REQUIRE(column[0] != 0);
		sortBot.updateScore(mineScore);
		REQUIRE(column.size() == 1);
		REQUIRE(sortBot.getScore() == mineScore);
	}

	SECTION("SortBot One Value Left To Mine")
	{
		column = { 2 };
		REQUIRE(sortBot.getScore() == 0);
		mineScore = sortBot.mine(&column);
		REQUIRE(column[0] == 0);
		sortBot.updateScore(mineScore);
		REQUIRE(column.size() == 1);
		REQUIRE(sortBot.getScore() == mineScore);
	}

	SECTION("SortBot Valid Empty Column")
	{
		column = { 0 };
		REQUIRE(sortBot.getScore() == 0);
		mineScore = sortBot.mine(&column);
		REQUIRE(column[0] == 0);
		sortBot.updateScore(mineScore);
		REQUIRE(column.size() == 1);
		REQUIRE(sortBot.getScore() == mineScore);
	}

	SECTION("SortBot Actual Empty Column")
	{
		REQUIRE(sortBot.getScore() == 0);
		CHECK_THROWS_AS(sortBot.mine(&column), std::logic_error);
	}
}

TEST_CASE("TripleBot Movement Tests", "[TripleBot::TripleBot][move]")
{
	srand(time(NULL));
	TripleBot tripleBot(true);
	Position startPos = tripleBot.getPos();
	
	SECTION("TripleBot Constructor")
	{
		REQUIRE(tripleBot.getPos().x >= 0);
		REQUIRE(tripleBot.getPos().x <= 4);
		REQUIRE(tripleBot.getPos().y >= 0);
		REQUIRE(tripleBot.getPos().y <= 4);
		REQUIRE(tripleBot.getScore() == 0);
	}

	SECTION("TripleBot Move Up")
	{
		for (int i = 0; i < 5; i++)
		{
			if (startPos.y == 0)
			{
				CHECK_THROWS_AS(tripleBot.move('w'), std::out_of_range);
				REQUIRE(tripleBot.getPos().y == startPos.y);
			}
			else
			{
				tripleBot.move('w');
				REQUIRE(tripleBot.getPos().y == startPos.y - 1);
			}
			REQUIRE(tripleBot.getPos().x == startPos.x);
			REQUIRE(tripleBot.getPos().x >= 0);
			REQUIRE(tripleBot.getPos().x <= 4);
			REQUIRE(tripleBot.getPos().y >= 0);
			REQUIRE(tripleBot.getPos().y <= 4);
			startPos = tripleBot.getPos();
		}
	}

	SECTION("TripleBot Move Down")
	{
		for (int i = 0; i < 5; i++)
		{
			if (startPos.y == 4)
			{
				CHECK_THROWS_AS(tripleBot.move('s'), std::out_of_range);
				REQUIRE(tripleBot.getPos().y == startPos.y);
			}
			else
			{
				tripleBot.move('s');
				REQUIRE(tripleBot.getPos().y == startPos.y + 1);
			}
			REQUIRE(tripleBot.getPos().x == startPos.x);
			REQUIRE(tripleBot.getPos().x >= 0);
			REQUIRE(tripleBot.getPos().x <= 4);
			REQUIRE(tripleBot.getPos().y >= 0);
			REQUIRE(tripleBot.getPos().y <= 4);
			startPos = tripleBot.getPos();
		}
	}

	SECTION("TripleBot Move Left")
	{
		for (int i = 0; i < 5; i++)
		{
			if (startPos.x == 0)
			{
				CHECK_THROWS_AS(tripleBot.move('a'), std::out_of_range);
				REQUIRE(tripleBot.getPos().x == startPos.x);
			}
			else
			{
				tripleBot.move('a');
				REQUIRE(tripleBot.getPos().x == startPos.x - 1);
			}
			REQUIRE(tripleBot.getPos().y == startPos.y);
			REQUIRE(tripleBot.getPos().x >= 0);
			REQUIRE(tripleBot.getPos().x <= 4);
			REQUIRE(tripleBot.getPos().y >= 0);
			REQUIRE(tripleBot.getPos().y <= 4);
			startPos = tripleBot.getPos();
		}
	}

	SECTION("TripleBot Move Right")
	{
		for (int i = 0; i < 5; i++)
		{
			if (startPos.x == 4)
			{
				CHECK_THROWS_AS(tripleBot.move('d'), std::out_of_range);
				REQUIRE(tripleBot.getPos().x == startPos.x);
			}
			else
			{
				tripleBot.move('d');
				REQUIRE(tripleBot.getPos().x == startPos.x + 1);
			}
			REQUIRE(tripleBot.getPos().y == startPos.y);
			REQUIRE(tripleBot.getPos().x >= 0);
			REQUIRE(tripleBot.getPos().x <= 4);
			REQUIRE(tripleBot.getPos().y >= 0);
			REQUIRE(tripleBot.getPos().y <= 4);
			startPos = tripleBot.getPos();
		}
	}
	
	SECTION("TripleBot Invalid Moves")
	{
		CHECK_THROWS_AS(tripleBot.move('N'), std::invalid_argument);
		CHECK_THROWS_AS(tripleBot.move(' '), std::invalid_argument);
		CHECK_THROWS_AS(tripleBot.move('1'), std::invalid_argument);
		CHECK_THROWS_AS(tripleBot.move('!'), std::invalid_argument);
	}
	
}

TEST_CASE("TripleBot Score Tests", "[TripleBot::TripleBot][score]")
{
	srand(time(NULL));
	TripleBot tripleBot(true);
	int score = 0;

	SECTION("TripleBot Get Score")
	{
		REQUIRE(tripleBot.getScore() == 0);
	}

	SECTION("TripleBot Update Score")
	{
		score = rand() % 100 + 1;
		tripleBot.updateScore(score);
		REQUIRE(tripleBot.getScore() == score);
	}
}

TEST_CASE("TripleBot Mining Tests", "[TripleBot::TripleBot][mine]")
{
	srand(time(NULL));
	TripleBot tripleBot(true);
	std::vector<int> column;
	int columnSize;
	int mineScore = 0;

	SECTION("TripleBot Full Column Mine Once")
	{
		column = { 1, 2, 3, 8, 6, 8, 5, 1, 5, 6 };
		columnSize = column.size();
		REQUIRE(tripleBot.getScore() == 0);
		mineScore = tripleBot.mine(&column);
		tripleBot.updateScore(mineScore);
		REQUIRE(column.size() == columnSize - 3);
		REQUIRE(tripleBot.getScore() == mineScore);
	}

	SECTION("TripleBot Three Values Left To Mine")
	{
		column = { 2, 1, 3 };
		REQUIRE(tripleBot.getScore() == 0);
		mineScore = tripleBot.mine(&column);
		tripleBot.updateScore(mineScore);
		REQUIRE(column.size() == 1);
		REQUIRE(tripleBot.getScore() == mineScore);
	}

	SECTION("TripleBot Two Values Left To Mine")
	{
		column = { 2, 1 };
		REQUIRE(tripleBot.getScore() == 0);
		mineScore = tripleBot.mine(&column);
		tripleBot.updateScore(mineScore);
		REQUIRE(column.size() == 1);
		REQUIRE(tripleBot.getScore() == mineScore);
	}

	SECTION("TripleBot One Value Left To Mine")
	{
		column = { 2 };
		REQUIRE(tripleBot.getScore() == 0);
		mineScore = tripleBot.mine(&column);
		REQUIRE(column[0] == 0);
		tripleBot.updateScore(mineScore);
		REQUIRE(column.size() == 1);
		REQUIRE(tripleBot.getScore() == mineScore);
	}

	SECTION("TripleBot Valid Empty Column")
	{
		column = { 0 };
		REQUIRE(tripleBot.getScore() == 0);
		mineScore = tripleBot.mine(&column);
		REQUIRE(column[0] == 0);
		tripleBot.updateScore(mineScore);
		REQUIRE(column.size() == 1);
		REQUIRE(tripleBot.getScore() == mineScore);
	}

	SECTION("TripleBot Actual Empty Column")
	{
		REQUIRE(tripleBot.getScore() == 0);
		CHECK_THROWS_AS(tripleBot.mine(&column), std::logic_error);
	}
}

TEST_CASE("RandomBot Movement Tests", "[RandomBot::RandomBot][move]")
{
	srand(time(NULL));
	RandomBot randomBot(true);
	Position startPos = randomBot.getPos();
	
	SECTION("RandomBot Constructor")
	{
		REQUIRE(randomBot.getPos().x >= 0);
		REQUIRE(randomBot.getPos().x <= 4);
		REQUIRE(randomBot.getPos().y >= 0);
		REQUIRE(randomBot.getPos().y <= 4);
		REQUIRE(randomBot.getScore() == 0);
	}

	SECTION("RandomBot Move Up")
	{
		for (int i = 0; i < 5; i++)
		{
			if (startPos.y == 0)
			{
				CHECK_THROWS_AS(randomBot.move('w'), std::out_of_range);
				REQUIRE(randomBot.getPos().y == startPos.y);
			}
			else
			{
				randomBot.move('w');
				REQUIRE(randomBot.getPos().y == startPos.y - 1);
			}
			REQUIRE(randomBot.getPos().x == startPos.x);
			REQUIRE(randomBot.getPos().x >= 0);
			REQUIRE(randomBot.getPos().x <= 4);
			REQUIRE(randomBot.getPos().y >= 0);
			REQUIRE(randomBot.getPos().y <= 4);
			startPos = randomBot.getPos();
		}
	}

	SECTION("RandomBot Move Down")
	{
		for (int i = 0; i < 5; i++)
		{
			if (startPos.y == 4)
			{
				CHECK_THROWS_AS(randomBot.move('s'), std::out_of_range);
				REQUIRE(randomBot.getPos().y == startPos.y);
			}
			else
			{
				randomBot.move('s');
				REQUIRE(randomBot.getPos().y == startPos.y + 1);
			}
			REQUIRE(randomBot.getPos().x == startPos.x);
			REQUIRE(randomBot.getPos().x >= 0);
			REQUIRE(randomBot.getPos().x <= 4);
			REQUIRE(randomBot.getPos().y >= 0);
			REQUIRE(randomBot.getPos().y <= 4);
			startPos = randomBot.getPos();
		}
	}

	SECTION("RandomBot Move Left")
	{
		for (int i = 0; i < 5; i++)
		{
			if (startPos.x == 0)
			{
				CHECK_THROWS_AS(randomBot.move('a'), std::out_of_range);
				REQUIRE(randomBot.getPos().x == startPos.x);
			}
			else
			{
				randomBot.move('a');
				REQUIRE(randomBot.getPos().x == startPos.x - 1);
			}
			REQUIRE(randomBot.getPos().y == startPos.y);
			REQUIRE(randomBot.getPos().x >= 0);
			REQUIRE(randomBot.getPos().x <= 4);
			REQUIRE(randomBot.getPos().y >= 0);
			REQUIRE(randomBot.getPos().y <= 4);
			startPos = randomBot.getPos();
		}
	}

	SECTION("RandomBot Move Right")
	{
		for (int i = 0; i < 5; i++)
		{
			if (startPos.x == 4)
			{
				CHECK_THROWS_AS(randomBot.move('d'), std::out_of_range);
				REQUIRE(randomBot.getPos().x == startPos.x);
			}
			else
			{
				randomBot.move('d');
				REQUIRE(randomBot.getPos().x == startPos.x + 1);
			}
			REQUIRE(randomBot.getPos().y == startPos.y);
			REQUIRE(randomBot.getPos().x >= 0);
			REQUIRE(randomBot.getPos().x <= 4);
			REQUIRE(randomBot.getPos().y >= 0);
			REQUIRE(randomBot.getPos().y <= 4);
			startPos = randomBot.getPos();
		}
	}

	SECTION("RandomBot Invalid Moves")
	{
		CHECK_THROWS_AS(randomBot.move('N'), std::invalid_argument);
		CHECK_THROWS_AS(randomBot.move(' '), std::invalid_argument);
		CHECK_THROWS_AS(randomBot.move('1'), std::invalid_argument);
		CHECK_THROWS_AS(randomBot.move('!'), std::invalid_argument);
	}
}

TEST_CASE("RandomBot Score Tests", "[RandomBot::RandomBot][score]")
{
	srand(time(NULL));
	RandomBot randomBot(true);
	int score = 0;

	SECTION("RandomBot Get Score")
	{
		REQUIRE(randomBot.getScore() == 0);
	}

	SECTION("RandomBot Update Score")
	{
		score = rand() % 100 + 1;
		randomBot.updateScore(score);
		REQUIRE(randomBot.getScore() == score);
	}
}

TEST_CASE("RandomBot Mining Tests", "[RandomBot::RandomBot][mine]")
{
	srand(time(NULL));
	RandomBot randomBot(true);
	std::vector<int> column;
	int columnSize;
	int mineScore = 0;

	SECTION("RandomBot Full Column Mine Once")
	{
		column = { 1, 2, 3, 8, 6, 8, 5, 1, 5, 6 };
		columnSize = column.size();
		REQUIRE(randomBot.getScore() == 0);
		mineScore = randomBot.mine(&column);
		REQUIRE(column.size() == columnSize - 2);
		randomBot.updateScore(mineScore);
		REQUIRE(randomBot.getScore() == mineScore);
	}

	SECTION("RandomBot Three Values Left To Mine")
	{
		column = { 2,1,3 };
		REQUIRE(randomBot.getScore() == 0);
		mineScore = randomBot.mine(&column);
		REQUIRE(column.size() == 1);
		randomBot.updateScore(mineScore);
		REQUIRE(randomBot.getScore() == mineScore);
	}

	SECTION("RandomBot Two Values Left To Mine")
	{
		column = { 2, 1 };
		REQUIRE(randomBot.getScore() == 0);
		mineScore = randomBot.mine(&column);
		REQUIRE(column.size() == 1);
		randomBot.updateScore(mineScore);
		REQUIRE(randomBot.getScore() == mineScore);
	}

	SECTION("RandomBot One Value Left To Mine")
	{
		column = { 2 };
		REQUIRE(randomBot.getScore() == 0);
		mineScore = randomBot.mine(&column);
		REQUIRE(column[0] == 0);
		randomBot.updateScore(mineScore);
		REQUIRE(column.size() == 1);
		REQUIRE(randomBot.getScore() == mineScore);
	}

	SECTION("RandomBot Valid Empty Column")
	{
		column = { 0 };
		REQUIRE(randomBot.getScore() == 0);
		mineScore = randomBot.mine(&column);
		REQUIRE(column[0] == 0);
		REQUIRE(column.size() == 1);
		randomBot.updateScore(mineScore);
		REQUIRE(randomBot.getScore() == mineScore);
	}

	SECTION("RandomBot Actual Empty Column")
	{
		REQUIRE(randomBot.getScore() == 0);
		CHECK_THROWS_AS(randomBot.mine(&column), std::logic_error);
	}
}