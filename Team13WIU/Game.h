#pragma once
#include "Entity.h"
class Game
{
private:
	Entity* gameObjects[3];
	Position playerPos;
	bool InTown = true;

public:
	Game();
	~Game();
	void GtypeLine(const std::string& text, int delay);
	void initGame();
	void drawWorld();
	void doTurn();
};

