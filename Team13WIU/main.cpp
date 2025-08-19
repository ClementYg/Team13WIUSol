#include <iostream>
#include <string>
#include "NPC.h"
#include "Position.h"

int main() {
	NPC villager("Old villager", 5, 1);
	villager.setX(1);
	villager.setY(5);
	villager.NPCtalk();
}