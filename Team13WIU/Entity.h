#pragma once
#include "Position.h"
#include <string>


class Entity
{
protected:
	Position pos;
	char symbol;
	bool IsActive;

public:
	Entity();
	~Entity();
	int getX() const;
	int getY() const;
	void setPosition(int x, int y);
	char getSymbol() const;
	void setSymbol(char s);
	bool getActive();
	void setActive(bool);
	virtual void move(Entity* gameObjects[], int size) = 0;
};

