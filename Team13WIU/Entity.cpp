#include "Entity.h"



Entity::Entity(int row, int col, char s) : pos(row, col), symbol(s) {}


const Position& Entity::getPosition() const
{
    return pos;
}


void Entity::setPosition(Position p) {
    pos = p;
}

char Entity::getSymbol() const {
    return symbol;
}

void Entity::setSymbol(char s) {
    symbol = s;
}

void Entity::move(Entity* gameObjects[], int size) {
    // Update the position of the entity
    // This method can be overridden in derived classes for specific movement logic
}