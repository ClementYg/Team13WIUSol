#include <iostream>
#include <string>
#include "NPC.h"
#include "Position.h"

int main() {
	NPC villager("Old villager", 5, 1);
	NPC villager2("Young villager", 6, 7);
	villager.setX(1);
	villager.setY(5);
	villager.NPCtalk();
	villager2.NPCtalk();
}