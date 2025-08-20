#pragma once
#include "Position.h"
#include <string>
#include <vector>

class NPC
{
protected:
	Position NPCspos;
	std::string name;
	std::vector<std::string> dialogue;

public:
	NPC(std::string n, int x, int y, std::vector<std::string> lines = {});
	virtual ~NPC();
	void setX(int x);
	void setY(int y);
	int getX() const;
	int getY() const;
	void typeLine(const std::string& text, int delay);

	virtual void NPCtalk();
};

