#include "Player.h"
#include "Game.h"
#include "conio.h"
#include <iostream>


Player::Player(std::string n, int y, int x, char s) : Morale(43) /*: Entity(row, col, '@') */
{
	name = n;
	pos.x = x;
	pos.y = y;
	symbol = s;
	interaction = false;
	moveinter = false;
}

Player::~Player() {

}


void Player::move(Entity* gameObjects[], int entityCount) {
	char input = _getch();
	int newRow = pos.y;
	int newCol = pos.x;
	// getX and getY
	interaction = false;
	moveinter = false;
	if (input == 'w') newRow--;
	else if (input == 's') newRow++;
	else if (input == 'a') newCol--;
	else if (input == 'd') newCol++;
	else if (input == 'z') Morale--;
	else if (input == 'x') Morale++;
	else if (input == ' ') interaction = true, moveinter = true;
	else return;//go back to game.cpp (forefeit turn)

	if (newRow >= 0 && newRow < 5 && newCol >= 0 && newCol < 49) {
		pos.x = newCol;
		pos.y = newRow;
	}
}

int Player::getMorale()
{
	return Morale;
}

void Player::setMorale(int newMorale)
{
	Morale = newMorale;
}

bool Player::interactionGet()
{
	return interaction;
}

bool Player::movingGet()
{
	return moveinter;
}