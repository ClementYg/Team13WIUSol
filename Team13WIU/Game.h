#pragma once
#include "Entity.h"
class Game
{
private:
	Entity* gameObjects[2];
	std::string dingle;
	Position playerPos;
	bool InTown;
	bool InForest;

public:
	Game();
	~Game();
	void GtypeLine(const std::string& text, int delay);
	void initGame();
	void drawWorld();
	void doTurn();
};

