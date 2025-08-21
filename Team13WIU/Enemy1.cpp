#include "Enemy1.h"
#include <iostream>
using namespace std;

Enemy1::Enemy1(std::string n, int y, int x, char s)
{
    name = n;
    pos.x = x;
    pos.y = y;
    symbol = s;
}

Enemy1::~Enemy1()
{

}

void Enemy1::move(Entity* gameObjects[], int entityCount) {
    // Not used in this implementation
}


void Enemy1::move(Position playerPos, Entity* gameobjects[], int entityCount)
{
    /*int curRow = pos.getRow();
	int curCol = pos.getCol();

    if (playerPos.getRow() <= curRow + 1 && playerPos.getRow() >= curRow - 1) {
        if (playerPos.getCol() <= curCol + 1 && playerPos.getCol() >= curCol - 1) {
            cout << "Interacting with bro" << endl;
        }
    }*/

}

//void Enemy1::move(Position playerPos, Entity* gameObjects[], int entityCount) {};
/*void Enemy1::move(Position playerPos, Entity* gameObjects[], int entityCount)
{
    int curRow = pos.getRow();
    int curCol = pos.getCol();
    int newRow = curRow;
    int newCol = curCol;

    // --- If not on the same row, try vertical step toward player ---
    if (playerPos.getRow() != curRow) {
        int targetRow = curRow;
        if (playerPos.getRow() < curRow)
        {
            targetRow = curRow - 1;
        }
        else {
            targetRow = curRow + 1;
        }

        bool verticalBlocked = false;
        for (int i = 0; i < entityCount; i++) {
            if (gameObjects[i] != nullptr && gameObjects[i] != this) {
                Position otherPos = gameObjects[i]->getPosition();
                if (otherPos.getRow() == targetRow && otherPos.getCol() == curCol) {
                    // allow capture: don’t treat as blocked if it’s the player’s tile
                    if (!(otherPos.getRow() == playerPos.getRow() && otherPos.getCol() == playerPos.getCol())) {
                        verticalBlocked = true;
                    }
                }
            }
        }

        if (!verticalBlocked && targetRow >= 0 && targetRow < 24) {
            newRow = targetRow;
            pos.setPosition(newRow, newCol);
            return; // moved vertically; no need to check horizontal
        }
        // else fall through to horizontal
    }

    // --- Try horizontal step toward player ---
    if (playerPos.getCol() != curCol) {
        int targetCol = curCol;
        if (playerPos.getCol() < curCol) targetCol = curCol - 1;
        else targetCol = curCol + 1;

        bool horizontalBlocked = false;
        for (int j = 0; j < entityCount; j++) {
            if (gameObjects[j] != nullptr && gameObjects[j] != this) {
                Position otherPos = gameObjects[j]->getPosition();
                if (otherPos.getRow() == curRow && otherPos.getCol() == targetCol) {
                    if (!(otherPos.getRow() == playerPos.getRow() && otherPos.getCol() == playerPos.getCol())) {
                        horizontalBlocked = true;
                    }
                }
            }
        }

        if (!horizontalBlocked && targetCol >= 0 && targetCol < 60) {
            newCol = targetCol;
        }
    }

    pos.setPosition(newRow, newCol);
}*/