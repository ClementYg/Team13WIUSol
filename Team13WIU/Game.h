#pragma once
#include "Entity.h"
#include "Puzzle.h"
class Game
{
private:
	Entity* gameObjects[3];
	Position playerPos;
	Puzzle* RiverPuzzle;
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
