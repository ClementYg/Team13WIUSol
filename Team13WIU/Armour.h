#pragma once
#include "Item.h"
class Armour : public Item
{

public:

	std::string getItemName();
	Armour(std::string n);
	virtual ~Armour();
};

