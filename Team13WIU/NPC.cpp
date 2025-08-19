#include "NPC.h"
#include <string>
#include <iostream>

// Create a NPC and tell its position
NPC::NPC(std::string n, int x, int y)
{
	name = n;
	NPCspos.x = x;
	NPCspos.y = y;
	std::cout << name << " spawned at (" << NPCspos.x << ',' << NPCspos.y << ")\n";
}

// Destroy NPC to free memory
NPC::~NPC()
{
	std::cout << name << " at " << '(' << NPCspos.x << ',' << NPCspos.y << ')' << " is deleted\n";
}

// function to set X position
void NPC::setX(int x)
{
	NPCspos.x = x;
}

// function to set Y position
void NPC::setY(int y)
{
	NPCspos.y = y;
}

// function to get X position
int NPC::getX() const
{
	return NPCspos.x;
}

// function to get Y position
int NPC::getY() const
{
	return NPCspos.y;
}

// function that make the NPC talk
void NPC::NPCtalk()
{
	std::cout << "(Mission Talk)" << std::endl;
}