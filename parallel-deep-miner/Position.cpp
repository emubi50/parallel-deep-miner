#include "Position.h"

Position::Position()
{
	this->x = 0;
	this->y = 0;
}

Position::Position(int x, int y)
{
	this->x = x;
	this->y = y;
}

Position::~Position()
{
}

Position& Position::operator+=(const Position& other)
{
	x += other.x;
	y += other.y;
	return *this;
}

Position& Position::operator-=(const Position& other)
{
	x -= other.x;
	y -= other.y;
	return *this;
}

Position& Position::operator=(const Position& other)
{
	x = other.x;
	y = other.y;
	return *this;
}