#include "Player.h"
#include "conio.h"
#include <iostream>


Player::Player(int row, int col) : Entity(row, col, '@') {
	name = "Player";
}

Player::~Player() {

}


void Player::move(Entity* gameObjects[], int entityCount) {
	char input = _getch();
	int newRow = pos.getY();
	int newCol = pos.getX();

	if (input == 'w') newRow--;
	else if (input == 's') newRow++;
	else if (input == 'a') newCol--;
	else if (input == 'd') newCol++;
	else return;//go back to game.cpp (forefeit turn)

	if (newRow >= 0 && newRow < 20 && newCol >= 0 && newCol < 60) {
		pos.setPosition(newRow, newCol);
	}
	



}