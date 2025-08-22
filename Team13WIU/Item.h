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
	enum armourType {
		WOOD_HELM,
		WOOD_LEGGS,
		WOOD_CHEST,
		A_UNKNOWN
	};
	enum consumeType {
		HP_POT,
		MANA_POT,
		STRENGTH_POT,
		C_UNKNOWN
	};

	enum weaponType {
		WOOD_SWORD,
		FIRE_SWORD,
		W_UNKNOWN
	};

	//GETTERS
	int getItemID();
	virtual std::string getItemName(); 
	std::string getItemDesc();
	bool checkItemSelect(); // returns isitemSelected


	//SETTERS
	void addDesc(std::string description);
	void select(int selected); //function to change isitemSelected of that object to be true

	virtual void useItem();

	static Item* create(std::string name, consumeType consumableType = consumeType::C_UNKNOWN);
	static Item* create(std::string name, weaponType wType = weaponType::W_UNKNOWN);
	static Item* create(std::string name, armourType aType = armourType::A_UNKNOWN);


	//made static so that you can create specific item object outside of class
	Item(); //default constructor
	~Item();
};