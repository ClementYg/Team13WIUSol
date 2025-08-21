#pragma once
#include "Entity.h"
class Game
{
private:
	Entity* gameObjects[2];
	int turn;
	std::string dingle;
	Position playerPos;

public:
	Game();
	~Game();
	void GtypeLine(const std::string& text, int delay);
	void initGame();
	void drawWorld();
	void doTurn();
};

