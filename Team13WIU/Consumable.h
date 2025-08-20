#pragma once
#include "Item.h"

class Consumable : public Item
{
private:
public:
	std::string getItemName();

	Consumable(std::string n);
	virtual ~Consumable();
};

