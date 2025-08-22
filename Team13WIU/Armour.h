#pragma once
#include "Item.h"
class Armour : public Item
{

public:

	std::string getItemName();

	void useItem();

	Armour(std::string n, armourType);
	virtual ~Armour();

private:
	armourType itemAType;
};

