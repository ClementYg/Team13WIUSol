#pragma once
#include "Item.h"

class Consumable : public Item
{
public:
	std::string getItemName();

	void useItem();

	Consumable* duplicate();

	Consumable(std::string n, consumeType, int, int);
	virtual ~Consumable();
private:
	consumeType itemCType;
	std::string name;
	int price;
};

