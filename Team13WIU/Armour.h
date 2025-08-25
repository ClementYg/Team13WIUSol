#pragma once
#include "Item.h"
class Armour : public Item
{

public:

	std::string getItemName();

	void useItem();
	Armour* duplicate();
	Armour(std::string n, armourType, int, int);
	virtual ~Armour();

private:
	armourType itemAType;
};

