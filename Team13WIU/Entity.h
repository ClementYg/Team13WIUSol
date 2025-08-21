#pragma once
#include "Position.h"
#include <string>


class Entity
{
protected:
	Position pos;
	char symbol;

public:
	Entity();
	~Entity();
	int getX() const;
	int getY() const;
	void setPosition(int x, int y);
	char getSymbol() const;
	void setSymbol(char s);
	virtual void move(Entity* gameObjects[], int size) = 0;
};

