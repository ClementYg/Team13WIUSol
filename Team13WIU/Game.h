#pragma once
#include "Entity.h"
class Game
{
private:
	Entity* gameObjects[10];
	Position playerPos;

	bool InInn;
	bool InTown;
	bool InForest;
	bool InHarbour;
	bool InOusideCave;
	bool InInsideCave;
	bool NarraInn;
	bool NarraTown;
	

public:
	Game();
	~Game();
	void GtypeLine(const std::string& text, int delay);
	void initGame();
	void drawWorld();
	void doTurn();
};

