#pragma once
#include "Entity.h"
class Game
{
private:
	Entity* gameObjects[2];
	int turn;

public:
	Game();
	~Game();
	void initGame();
	void drawWorld();
	void doTurn();
};

