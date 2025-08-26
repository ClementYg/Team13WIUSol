#pragma once
#include "Entity.h"
#include <windows.h>
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
	bool NarraForest;
	bool NarraHarbour;
	bool NarraOutsideCave;
	bool NarraInsideCave;



public:
	Game();
	~Game();
	void GtypeLine(const std::string& text, int delay);
	void initGame();
	void drawWorld();
	void doTurn();
	void clearDialogue();
};

