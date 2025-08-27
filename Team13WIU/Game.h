#pragma once
#include "Entity.h"
#include "Puzzle.h"
class Game
{
private:
	Entity* gameObjects[10];
	Position playerPos;
	//Puzzle* RiverPuzzle;

	bool InInn;
	bool InTown;
	bool InForest;
	bool InHarbour;
	bool InOusideCave;
	bool InInsideCave;
	bool NarraInn;
	bool NarraTown;
	bool puzzleActive;
	

public:
	Game();
	~Game();
	void GtypeLine(const std::string& text, int delay);
	void initGame();
	void drawWorld();
	void doTurn();
};
