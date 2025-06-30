#pragma once
class Position
{
public:
	int x, y;
	Position();
	Position(int x, int y);
	~Position();
	Position& operator+=(const Position& other);
	Position& operator-=(const Position& other);
	Position& operator=(const Position& other);
};

