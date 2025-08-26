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
	int price;
	int quantity;
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
		STEEL_SWORD,
		W_UNKNOWN
	};

	//GETTERS
	int getItemID();
	void setItemID(int change); 
	virtual int getPrice();
	virtual std::string getItemName(); 
	std::string getItemDesc();
	bool checkItemSelect(); // returns isitemSelected
	int getQuantity();

	//SETTERS
	void addDesc(std::string description);
	void select(int selected); //function to change isitemSelected of that object to be true
	void setQuantity(int change);


	virtual Item* duplicate() = 0;
	virtual void useItem();

	static Item* create(std::string name, consumeType consumableType = consumeType::C_UNKNOWN, int price = 0, int qty = 1);
	static Item* create(std::string name, weaponType wType = weaponType::W_UNKNOWN, int price = 0, int qty = 1);
	static Item* create(std::string name, armourType aType = armourType::A_UNKNOWN, int price = 0, int qty = 1);


	//made static so that you can create specific item object outside of class
	Item(); //default constructor
	~Item();
};