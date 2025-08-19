#pragma once
#include <string>
class Item
{
private:
	std::string name;
	std::string itemDesc;
	int itemID;
	static int IDCounter;
	bool isitemSelected;

public: 	
	enum Types {
		CONSUMABLES,
		//ANYTHING BELOW IS SUBJECT TO CHANGE. ONLY CONFIRMED IS CONSUMABLES
		WEAPON,
		ARMOUR
	};


	//GETTERS
	int getItemID();
	std::string getItemName(); 
	std::string getItemDesc();
	bool checkItemSelect(); // returns isitemSelected


	//SETTERS
	void addDesc(std::string description);
	void select(int selected); //function to change isitemSelected of that object to be true
	Item* create(Types itemtype);
	Item(std::string name);
	~Item();
	
private:
	Types createType;

};