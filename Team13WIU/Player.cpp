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
	inPuzzle = false;
	playerInv = new Inventory;
	playerHP = MAX_HP;
	playerMana = MAX_MANA; 
}

Player::~Player() {
	delete playerInv;
}

Inventory* Player::getInv()
{
	return playerInv;
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
	else if (input == 'i') playerInv->requestInventory(this); 
	else return;//go back to game.cpp (forefeit turn)
	if (inPuzzle)
	{

		if (newRow >= 0 && newRow < 20 && newCol >= 0 && newCol < 49) {
			pos.x = newCol;
			pos.y = newRow;
		}
	}
	else 
	{
		if (newRow >= 0 && newRow < 5 && newCol >= 0 && newCol < 49) {
			pos.x = newCol;
			pos.y = newRow;
		}
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
// void Player::puzzleSet(int newPuzzle)
// {
// 	inPuzzle = newPuzzle;
// }

int Player::getMaxHP()
{
	return MAX_HP;
}

int Player::getMaxMana() {
	return MAX_MANA;
}

void Player::setPlayerX(int newValue) { playerX = newValue; }
void Player::setPlayerY(int newValue) { playerY = newValue; }

void Player::addPlayerX(int change) { playerX += change; }
void Player::addPlayerY(int change) { playerY += change; }

int Player::getPlayerX() { return playerX; }
int Player::getPlayerY() { return playerY; }

int Player::getPlayerHP()
{
	return playerHP;
}

int Player::getPlayerMana() {
	return playerMana;
}

void Player::addPlayerHP(int change)
{
	playerHP += change;

	if (playerHP < 0) {
		playerHP = 0; //make sure cannot go below 0. basically same as cnt go below 0.
	}
}

void Player::addPlayerMana(int change) {
	playerMana += change; 

	if (playerMana < 0) {
		playerMana = 0;
	}
}

//INITIALISATIONS
