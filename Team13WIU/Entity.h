#pragma once
#include "Position.h"
#include <string>


class Entity : public Position
{
protected:
	Position pos;
	char symbol;

public:
	Entity(int row, int col, char s);
	const Position& getPosition() const;
	void setPosition(Position p);
	char getSymbol() const;
	void setSymbol(char s);
	virtual void move(Entity* gameObjects[], int size) = 0;
};

