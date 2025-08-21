#include "Game.h"
#include <iostream>

int main() {
<<<<<<< HEAD
	// make sure define every NPC's speech before hand
	std::vector<std::string> OldVillagerlines =
	{
		"Hey hey, small boy!",
		"I am the Old Villager, before you go I have a quest for you", 
		"Be gay and come back to me for reward!"
	};

	std::vector<std::string> Merchantlines =
	{
		"Hey I am a Merchant.",
		"Do you want to buy anything or sell anything?",
		"I have all the things in this world!"
	};

	std::vector<std::string> Masterlines =
	{
		"I am your master.",
		"I am going to teach you basic fighting skills",
		"Hope you won't get hurt or killed"
	};

	std::vector<std::string> BMOlines =
	{
		"What a strong guy!",
		"Your arm muscles are perfect!",
		"Join this competition, if you win I will reward you something crazy"
	};

	// create NPC type and the informations(name, x, y, speech)
	NPC villager("Old villager", 5, 1, OldVillagerlines);
	Merchant clement("Clement", 2, 4, Merchantlines);
	Master Spencer("Spencer", 3, 4, Masterlines);
	BMOrganiser KaiZher("KaiZher", 4, 4, BMOlines);

	// make them talk or do something like trade()
	villager.NPCtalk();
	clement.NPCtalk();
	clement.trade();
	Spencer.NPCtalk();
	KaiZher.NPCtalk();
	KaiZher.setX(5);

=======
	Game game;
	game.initGame();

	while (true) {
		game.doTurn();
	}
	return 0;
>>>>>>> parent of f56483a (Update main.cpp)
}