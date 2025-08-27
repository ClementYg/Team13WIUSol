#pragma once
#include "Position.h"
#include "Entity.h"
#include <string>
#include <vector>

class NPC : public Entity
{
public:
	std::string name;
	std::vector<std::string> dialogue;
	NPC(std::string n, int y, int x, char s,std::vector<std::string> lines = {});
	~NPC();

	void typeLine(const std::string& text, int delay);
	void move(Entity* gameObjects[], int size);

	virtual void NPCtalk();
};