#pragma once
#include "Position.h"
#include <string>


class Entity
{
protected:
	char symbol;
	bool IsActive;

public:
	Position pos;

	Entity();
	~Entity();
	int getX() const;
	int getY() const;
	void setPosition(int x, int y);
	char getSymbol() const;
	bool getActive();
	void setActive(bool);
	virtual void move(Entity* gameObjects[], int size) = 0;
};

