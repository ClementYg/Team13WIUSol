#include "Game.h"
#include "Player.h"
#include "Enemy1.h"
#include <iostream>
#include <cstdlib>
using namespace std;



Game::Game() : turn(0) {
    for (int i = 0; i < 2; ++i) gameObjects[i] = nullptr;
}

Game::~Game() {
    for (int i = 0; i < 2; ++i) {
        delete gameObjects[i];
        gameObjects[i] = nullptr;
    }
}

void Game::initGame() {
    gameObjects[0] = new Player(0, 0);
    gameObjects[1] = new Enemy1(5, 10);
}

void Game::drawWorld() {
    
    char grid[24][60];
    for (int r = 0; r < 24; ++r)
        for (int c = 0; c < 60; ++c)
            grid[r][c] = ' ';

    for (int i = 0; i < 2; ++i) {
        if (gameObjects[i] != nullptr) {
            int r = gameObjects[i]->getPosition().getRow();
            int c = gameObjects[i]->getPosition().getCol();
            if (r >= 0 && r < 24 && c >= 0 && c < 60) {
                grid[r][c] = gameObjects[i]->getSymbol();
            }
        }
    }

    for (int i = 0; i < 120; i++) {
        cout << '-';
		if (i == 119) cout << "\n"; // New line after the border
    }

    for (int r = 0; r < 24; ++r) {
        for (int c = 0; c < 60; ++c) cout << " " << grid[r][c];
        cout << " \n";
    }

	for (int i = 0; i < 120; i++) {
        cout << '-';
		if (i == 119) cout << "\n"; // New line after the border
    }

	cout << dingle << "\n";
 

    
}

void Game::doTurn() {
    // If player is gone, end game
    ++turn;
    system("cls"); // Clear console (Windows)
    cout << "Turn: " << turn << "\n";
    drawWorld();

    // Move player (guard the cast)
    Player* player = static_cast<Player*>(gameObjects[0]);

    if (player != nullptr) {
        player->move(gameObjects, 2);
    }



    // Move enemies
    for (int i = 1; i < 2; ++i) {
        if (gameObjects[i] != nullptr && player != nullptr) {
            Enemy1* enemy1 = static_cast<Enemy1*>(gameObjects[i]);
            // capture player's position before any possible deletion later
            Position playerPos = player->getPosition();
            enemy1->move(playerPos, gameObjects, 2);
        }
    }

    // Check collisions
    for (int i = 1; i < 2; ++i) {
        if (gameObjects[i] != nullptr && gameObjects[0] != nullptr) {
            if (gameObjects[i]->getPosition().equals(gameObjects[0]->getPosition())) {
                continue;   
            }
        }
    }
    if (gameObjects[0] != nullptr && gameObjects[1] != nullptr) {
        if (gameObjects[0]->getPosition().getRow() <= gameObjects[1]->getPosition().getRow() + 1 && gameObjects[0]->getPosition().getRow() >= gameObjects[1]->getPosition().getRow() - 1) {
            if (gameObjects[0]->getPosition().getCol() <= gameObjects[1]->getPosition().getCol() + 1 && gameObjects[0]->getPosition().getCol() >= gameObjects[1]->getPosition().getCol() - 1) {
                dingle = "Interacting with bro";
            }
        }
    }
}