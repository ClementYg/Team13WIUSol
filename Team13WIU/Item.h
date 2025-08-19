#pragma once
#include <string>
class Item
{
private:
	std::string name;
	int itemID;
	static int IDCounter;
	bool isitemSelected;
	//enum Types {
	//	CONSUMABLES,
	//	//ANYTHING BELOW IS SUBJECT TO CHANGE. ONLY CONFIRMED IS CONSUMABLES
	//	WEAPON,
	//	ARMOUR
	//};

	std::string itemDesc;
public: 	
	bool checkItemSelect();
	int getItemID();
	std::string getItemName(); 

	Item(std::string name);
	~Item();
};

