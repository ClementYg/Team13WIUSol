#include "Game.h"
#include <iostream>

int main() {
	Game game;
	game.initGame();

	while (true) {
		game.doTurn();
	}

	return 0;
}