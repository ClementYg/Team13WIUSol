#pragma once
#include "Position.h"
#include <string>

class NPC
{
protected:
	Position NPCspos;

private:
	std::string name;

public:

	NPC(std::string n, int x, int y);
	~NPC();
	void setX(int x);
	void setY(int y);
	int getX() const;
	int getY() const;

	void NPCtalk();
};

