#include "Entity.h"
#include <iostream>



Entity::Entity()
{

}

Entity::~Entity()
{

}


int Entity::getX() const
{
    return pos.x;
}

int Entity::getY() const
{
    return pos.y;
}


void Entity::setPosition(int x, int y) {
    pos.x = x;
    pos.y = y;
}

char Entity::getSymbol() const {
    return symbol;
}

void Entity::move(Entity* gameObjects[], int size) {
    // Update the position of the entity
    // This method can be overridden in derived classes for specific movement logic
}