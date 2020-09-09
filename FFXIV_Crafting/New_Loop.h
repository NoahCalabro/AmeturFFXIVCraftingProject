#pragma once

class  CraftingInfo
{
public:
	int MaxProgress;//
	//How much progress a crafting object needs to being completed.
	//Necessary to reach full in order to create the object
	int InitiProgress;//
	//Used if we start with some when redoing it
	int InitiQuality;//
	//How much quality a crafting object has.
	//Determines the chance of a high quality object.
	//Not necessary to be full, but better
	//This shows how much we start with
	int MaxQuality;//
	//Lists how much quality there is at the max
	int Durability;//
	//Crafting materials have a set durability, which is pretty much a list of the number of actions that can be done.
	//We take the durability and use it to determine an array size for the program
	float BaseProgress;//
	//Made from Craftsmanship
	int Control;//
	//Determines quality
	int CP;//
	//Determines the actions available, as each have cost
	int CLVL;//
	//Crafter's level
	int RLVL;//
	//Recipie's level
	int stars;//
	//Additional info for some levels
	int LevelMod;//
	//Level modification value.
};

class Buffs {
public:
	bool Good;
	bool Excellent;
	bool Poor;
	int InnerQuiet;
	int Veneration;
	int MuscleMemory;
	int GreatStrides;
	int Innovation;
	int WasteNot;
	int FinalAppriasal;
	int NameOfTheElements;
	bool Nameless;
	int Manipulation;
	int CarefulObservation;
	bool ObserveLast;
};

class Notes {
public:
	//Will be used for the array
	int Progress;
	int Quality;
	std::string actions;
	int step;
	Buffs statusBuffs;
	int Durability;
	int steps;
	CraftingInfo otherInfo;
};

Buffs updateBuffs(Buffs status);
std::vector<Notes> All_Skills(Buffs status, CraftingInfo info, int CurrentDur, int step, bool ManipulationAllow);