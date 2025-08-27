#pragma once
#include "Entity.h"
#include <vector>
#include <string>
class Game
{
private:
	Entity* gameObjects[13];
	Position playerPos;

	std::vector<std::string> InnKeeperSpeech =
	{
		"If you are wondering why are you here,",
		"A shadowed figure brought you here yesterday.",
		"You should head to the townsquare if you need help."
	};

	std::vector<std::string> TSvillagersBeforeSpeech =
	{
		"I can't help you much, but that man over there might be able to."
	};

	std::vector<std::string> TSBraveKnightSpeech =
	{
		"Civilian, how can I hel-",
		"Wait... You look familiar",
		"OHH! You are that villain!",
		"That has been killing the innocents.",
		"I will kill you in the name of justice!"
	};

	std::vector<std::string> TSvillagersAfterSpeech =
	{
		"He is the wanted villain!",
		"We need to call the royal guards NOW!"
		// MC run into forest to avoid getting arrest
	};

	std::vector<std::string> BearSpeech =
	{
		"RRAHHHHHH..."
	};

	std::vector<std::string> KidSpeech =
	{
		"OH MY GOD! That was so scary",
		"Thank you my hero, can you bring me back to my village?",
		"In case there are more monsters."
	};

	std::vector<std::string> HvillagersSpeech =
	{
		"The hero? I heard that he was last seen ouside the cave.",
		"The cave is at that island over there.",
		"It's impossible to get there without a ship."
	};

	//need interacting part for sneaking into the ship.

	std::vector<std::string> johnSpeech =
	{
		"Hi! I am John, A travelling merchant.",
		"I sell some interesting things.",
		"Do you want to take a look?"
	};

	std::vector<std::string> GHeroSpeech =
	{
		"MC! STOP THERE!",
		"You can't succumb to the devil's power",
		"Once you take it, there is no turning back.",
		"If you still choose to use that horrendous stink of a power",
		"I have no choice but to end your life on my terms!"
	};

	std::vector<std::string> BHeroSpeech =
	{
		"MC! I have already taken the devil's power.",
		"You were right, having this evil power is the meaning of life",
		"You are going to follow me down this path too, right?",
		"Anyways, you can't stop me even if you tried.",
		"Make your choice now, or die by my hands!"
	};

	bool InInn;
	bool InTown;
	bool InForest;
	bool InHarbour;
	bool InOusideCave;
	bool InInsideCave;
	bool NarraInn;
	bool NarraTown;
	bool BKAlive;
	bool BearAlive;
	

public:
	Game();
	~Game();
	void GtypeLine(const std::string& text, int delay);
	void initGame();
	void drawWorld();
	void doTurn();
};

