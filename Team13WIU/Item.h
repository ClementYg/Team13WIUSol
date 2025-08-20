#pragma once
#include <string>
class Item
{
private:
	std::string itemDesc;
	int itemID;
	static int IDCounter; //used to assign each ID to each Item based on order that is added to Inventory.
	bool isitemSelected;

protected:
	std::string name;
public: 	
	enum Types {
		CONSUMABLES,
		WEAPON,
		ARMOUR
	};


	//GETTERS
	int getItemID();
	virtual std::string getItemName(); 
	std::string getItemDesc();
	bool checkItemSelect(); // returns isitemSelected


	//SETTERS
	void addDesc(std::string description);
	void select(int selected); //function to change isitemSelected of that object to be true
	static Item* create(std::string name, Types itemtype); //made static so that you can create specific item object outside of class
	Item(); //default constructor
	~Item();
};