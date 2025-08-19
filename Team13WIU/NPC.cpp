#include "NPC.h"
#include <chrono>
#include <thread>
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
	std::string text;

	if (name == "Old villager") {
		text = "I am very very old, you have to get me some water and i will give you money";
	}
	else {
		text = "I am not Old villager, you find the wrong person";
	}

	for (char c : text) {
		std::cout << c << std::flush;          // print one character
		std::this_thread::sleep_for(std::chrono::milliseconds(30)); // wait 50ms
	}
	std::cout << std::endl;
}