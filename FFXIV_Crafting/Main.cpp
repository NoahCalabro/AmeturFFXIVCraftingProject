//A program to help determine the best method of crafting an object in FFXIV

#include <iostream>
#include <iomanip>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <conio.h>
#include "Actions.h"
#include "Equations.h"
#include "New_Loop.h"

/*
isParam
	Input:
		std::string line
	Output
		bool isParam
	Functionality
		Checks if the input is a number.
*/

bool isParam(std::string line) {
	char* p;
	strtol(line.c_str(), &p, 10);
	return *p == 0;
}

/*
getCLVL
	Output
		int CLVL
	Functionality
		Asks user for the CLVL value for later
*/

int getCLVL() 
{
	std::string level;
	int value;

	std::cout << "Please tell me your crafting level.\n";
	//Error check
	while (1)
	{
		std::cin >> level;

		if (!isParam(level)) {
			std::cout << "Sorry, it seems like that isn't an integer. Please try again.\n";
			continue;
		}

		value = std::stoi(level);

		if (value >= 1 && value <= 80) {
			break;
		}

		std::cout << "That is not in the level range. Please try again.\n";
	}

	

	return value;
}

/*
getRLVL
	Output
		int CLVL
	Functionality
		Asks user for the RLVL value for later, as well as any possible stars for the recipe
*/

std::pair <int, int> getRLVL() {
	std::string level;
	int value;

	std::cout << "Please tell me the crafting recipe's level.\n";
	//Error check
	while (1)
	{
		std::cin >> level;

		if (!isParam(level)) {
			std::cout << "Sorry, it seems like that isn't an integer. Please try again.\n";
			continue;
		}

		value = std::stoi(level);

		if (value >= 1 && value <= 80) {
			break;
		}

		std::cout << "That is not in the level range. Please try again.\n";
	}

	int RLVL = value;
	int stars;

	if (RLVL == 50 || RLVL == 60 || RLVL == 70) {
		std::cout << "How many stars does your recipe have? (0-4 Please)\n";
		while (1)
		{
			std::cin >> level;

			if (!isParam(level)) {
				std::cout << "Sorry, it seems like that isn't an integer. Please try again.\n";
				continue;
			}

			value = std::stoi(level);

			if (value >= 0 && value <= 4) {
				break;
			}

			std::cout << "That is not in the range. Please try again.\n";
		}
		stars = value;
	}
	else if (RLVL == 80) {
		std::cout << "How many stars does your recipe have? (0-3 Please)\n";
		while (1)
		{
			std::cin >> level;

			if (!isParam(level)) {
				std::cout << "Sorry, it seems like that isn't an integer. Please try again.\n";
				continue;
			}

			value = std::stoi(level);

			if (value >= 0 && value <= 3) {
				break;
			}

			std::cout << "That is not in the range. Please try again.\n";
		}
		stars = value;
	}
	else {
		stars = 0;
	}

	std::pair <int, int> LevelAndStars;
	LevelAndStars.first = RLVL;
	LevelAndStars.second = stars;

	return LevelAndStars;
}

/*
getCraftsmanship
	Output
		int Craftsmanship
	Functionality
		Asks user for the Craftsmanship value for later
*/

int getCraftsmanship() {
	std::string StringUse;
	int temp; 
	std::cout << "Please tell me your Craftsmanship stat.\n";

	while (1)
	{
		std::cin >> StringUse;

		if (!isParam(StringUse)) {
			std::cout << "Sorry, it seems like that isn't an integer. Please try again.\n";
			continue;
		}

		temp = std::stoi(StringUse);

		if (temp >= 0) {
			break;
		}

		std::cout << "A negative Craftsmanship shouldn't be possible. Try again.\n";
	}
	return temp;
}

/*
getControl
	Output
		int Control
	Functionality
		Asks user for the Control value for later
*/

int getControl() {
	std::string StringUse;
	int temp;
	std::cout << "Please tell me your Control stat.\n";

	while (1)
	{
		std::cin >> StringUse;

		if (!isParam(StringUse)) {
			std::cout << "Sorry, it seems like that isn't an integer. Please try again.\n";
			continue;
		}

		temp = std::stoi(StringUse);

		if (temp >= 0) {
			break;
		}

		std::cout << "A negative Control shouldn't be possible. Try again.\n";
	}
	return temp;
}

/*
getCP
	Output
		int CP
	Functionality
		Asks user for the CP value for later
*/

int getCP() {
	std::string StringUse;
	int temp;
	std::cout << "Please tell me your CP stat.\n";

	while (1)
	{
		std::cin >> StringUse;

		if (!isParam(StringUse)) {
			std::cout << "Sorry, it seems like that isn't an integer. Please try again.\n";
			continue;
		}

		temp = std::stoi(StringUse);

		if (temp >= 0) {
			break;
		}

		std::cout << "A negative CP shouldn't be possible. Try again.\n";
	}
	return temp;
}

/*
getDurability
	Output
		int Durability
	Functionality
		Asks user for the Durability value for later
*/

int getDurability() {
	std::string StringUse;
	int temp;
	std::cout << "Tell me the durability of the recipe.\n(The durability should be under the difficulty and item name)\n";

	while (1)
	{
		std::cin >> StringUse;

		if (!isParam(StringUse)) {
			std::cout << "Sorry, it seems like that isn't an integer. Please try again.\n";
			continue;
		}

		temp = std::stoi(StringUse);

		if (temp >= 0) {
			if (temp % 10 == 0) {
				break;
			}
			else {
				std::cout << "Most durability are in increments of ten. Try again.\n";
				continue;
			}
		}

		std::cout << "A negative durability shouldn't be possible. Try again.\n";
	}
	return temp;
}

/*
getMaxProgress
	Output
		int Max Progress
	Functionality
		Asks user for the Max Progress value for later
*/

int getMaxProgress() {
	std::string StringUse;
	int temp;
	//Finds the progress of the recipe
	std::cout << "What is the difficulty of the recipe?\n (Should be under the item name)\n";

	while (1)
	{
		std::cin >> StringUse;

		if (!isParam(StringUse)) {
			std::cout << "Sorry, it seems like that isn't an integer. Please try again.\n";
			continue;
		}

		temp = std::stoi(StringUse);

		if (temp >= 0) {
			break;
		}

		std::cout << "A negative difficulty shouldn't be possible. Try again.\n";
	}
	return temp;
}

/*
getDurability
	Output
		int Durability
	Functionality
		Asks user for the Durability value for later
*/

int getMaxQuality() {
	std::string StringUse;
	int temp;
	//Finds the quality 
	std::cout << "What is the max quality of the recipe?\n (Should be under the blue number that's to the right of the durability)\n";

	while (1)
	{
		std::cin >> StringUse;

		if (!isParam(StringUse)) {
			std::cout << "Sorry, it seems like that isn't an integer. Please try again.\n";
			continue;
		}

		temp = std::stoi(StringUse);

		if (temp >= 0) {
			break;
		}

		std::cout << "A negative quality shouldn't be possible. Try again.\n";
	}
	return temp;
}

/*
getInitialQuality
	Input
		int MaxQuality
	Output
		int InitalQuality
	Functionality
		Asks user for the InitalQuality value from high quality ingredients. Makes sure that it doesn't violate the 50% rule
*/

int getInitialQuality(int MaxQuality) {
	std::string StringUse;
	int temp;
	char HQIngredients;

	std::cout << "Are you adding high quality ingredients? (Y/N answer only please)\n";

	std::cin >> std::setw(1) >> HQIngredients;

	HQIngredients = std::toupper(HQIngredients);

	while (!std::cin.good() || (HQIngredients != 'Y' && HQIngredients != 'N')) {
		//Let's make sure it's a Yes or No Answer
		std::cout << "ERROR: That's not answer.\n";

		//Clear the stream
		std::cin.clear();
		std::cin.ignore(CHAR_MAX, '\n');


		std::cout << "Are you adding high quality ingredients? (Y/N answer only please)\n";
		std::cin >> std::setw(1) >> HQIngredients;
		HQIngredients = std::toupper(HQIngredients);
	}
	std::cin.clear();
	std::cin.ignore(CHAR_MAX, '\n');

	//If yes, get the proper value.
	if (HQIngredients == 'Y') {
		std::cout << "OK. Tell me how much quality is added. (The blue number)\n";

		

		while (1)
		{
			std::cin >> StringUse;

			if (!isParam(StringUse)) {
				std::cout << "Sorry, it seems like that isn't an integer. Please try again.\n";
				continue;
			}

			temp = std::stoi(StringUse);

			if (temp >= 0) {
				if (temp <= (MaxQuality / 2)) {
					break;
				}
				else {
					std::cout << "You can only get 50% of the max quality with ingredients. Please try again.\n";
					continue;
				}
			}

			std::cout << "A negative quality shouldn't be possible. Try again.\n";
		}
		return temp;
	}
	else {
		return 0;
	}
}

/*
getInitialQuality
	Output
		bool ManipulatoinAllow
	Functionality
		Asks if the user has completed a certain quest. This allows the possible use of a specific action
*/

bool manipulationCheck()
{
	char input;

	std::cout << "Have you completed your level 65 quest? (Y/N answer only please)\n";

	std::cin >> std::setw(1) >> input;

	input = std::toupper(input);

	//Error check
	while (!std::cin.good() || (input != 'Y' && input != 'N')) {
		//Let's make sure it's a Yes or No Answer
		std::cout << "ERROR: That's not answer.\n";

		//Clear the stream
		std::cin.clear();
		std::cin.ignore(CHAR_MAX, '\n');

		
		std::cout << "Have you completed your level 65 quest? (Y/N answer only please)\n";
		std::cin >> std::setw(1) >> input;
		input = std::toupper(input);
	}

	std::cin.clear();
	std::cin.ignore(CHAR_MAX, '\n');


	if (input == 'Y') {
		return true;
	}
	else {
		return false;
	}
}

/*
GoodCheck
	Output
		bool Good
	Functionality
		For when going through the steps. This asks the user if the condition is considered Good, which may alter what moves and effects are available. 
*/

bool GoodCheck() {
	char input;

	std::cout << "Is the Condition \"Good\"? (Y/N answer only please)\n";

	std::cin >> std::setw(1) >> input;

	input = std::toupper(input);

	//Error check
	while (!std::cin.good() || (input != 'Y' && input != 'N')) {
		//Let's make sure it's a Yes or No Answer
		std::cout << "ERROR: That's not answer.\n";

		//Clear the stream
		std::cin.clear();
		std::cin.ignore(CHAR_MAX, '\n');


		std::cout << "Is the Condition \"Good\"? (Y/N answer only please)\n";
		std::cin >> std::setw(1) >> input;
		input = std::toupper(input);
	}

	std::cin.clear();
	std::cin.ignore(CHAR_MAX, '\n');


	if (input == 'Y') {
		return true;
	}
	else {
		return false;
	}
}

/*
ExcellentCheck
	Output
		bool Excellent
	Functionality
		For when going through the steps. This asks the user if the condition is considered Excellent, which may alter what moves and effects are available.
*/

bool ExcellentCheck() {
	char input;

	std::cout << "Is the Condition \"Excellent\"? (Y/N answer only please)\n";

		std::cin >> std::setw(1) >> input;

	input = std::toupper(input);

	//Error check
	while (!std::cin.good() || (input != 'Y' && input != 'N')) {
		//Let's make sure it's a Yes or No Answer
		std::cout << "ERROR: That's not answer.\n";

		//Clear the stream
		std::cin.clear();
		std::cin.ignore(CHAR_MAX, '\n');


		std::cout << "Is the Condition \"Excellent\"? (Y/N answer only please)\n";
			std::cin >> std::setw(1) >> input;
		input = std::toupper(input);
	}

	std::cin.clear();
	std::cin.ignore(CHAR_MAX, '\n');


	if (input == 'Y') {
		return true;
	}
	else {
		return false;
	}
}

/*
GetInfo
	Output
		CraftingInfo Info
	Functionality
		Calls all the stuff from above, getting the information
*/

CraftingInfo GetInfo() {
	CraftingInfo stuff;

	std::string StringUse;
	int temp;

	std::cout << "Okay, let's get started. Find your character menu.\n";

	stuff.CLVL = getCLVL();

	int Crafts = getCraftsmanship();
	//Will be used later to find Base Progress.

	stuff.Control = getControl();
	//Control varies, so we're keeping that value

	stuff.CP = getCP();

	std::cout << "Okay, head over to your crafting item.\n";

	std::pair <int, int> temp1 = getRLVL();

	stuff.MaxProgress = getMaxProgress();

	stuff.Durability = getDurability();

	stuff.RLVL = temp1.first;

	stuff.stars = temp1.second;

	stuff.LevelMod = FindLevelMod(stuff.CLVL, stuff.RLVL);

	stuff.BaseProgress = BaseProgress(Crafts, stuff.RLVL, stuff.LevelMod, stuff.stars);
	
	stuff.MaxQuality = getMaxQuality();

	//Will there be a bonus to quality from high quality ingredients? If so, what is the quality bonus? 
	stuff.InitiQuality = getInitialQuality(stuff.MaxQuality);

	stuff.InitiProgress = 0;

	return stuff;

}

/*
GenerateStart
	Output
		Buffs Start
	Functionality
		Sets up inital status effects and values
*/

Buffs GenerateStart() {
	Buffs Start;
	
	Start.Good = false;
	Start.Excellent = false;
	Start.Poor = false;
	Start.InnerQuiet = 0;
	Start.Veneration = 0;
	Start.MuscleMemory = 0;
	Start.Innovation = 0;
	Start.WasteNot = 0;
	Start.FinalAppriasal = 0;
	Start.NameOfTheElements = 0;
	Start.Nameless = false;
	Start.Manipulation = 0;
	Start.CarefulObservation = 0;
	Start.ObserveLast = false;

	return Start;
}

/*
main
	Output
		0
	Functionality
		The main function. Calls all the functions to get info for crafting, then goes into the All_Skills function to find the sequence of actions. 
		Once it's found, it then goes through the list of actions, checking if any Good or Excellent conditions, and repeating the All_Skills function if necssary.
*/

int main()
{
	CraftingInfo item = GetInfo();


	Buffs startBuffs = GenerateStart();

	
	int level = item.CLVL;
	
	std::vector<Notes> List;

	bool ManipulationAllow;

	if (level < 65) {
		ManipulationAllow = false;
	}
	else {
		ManipulationAllow = manipulationCheck();
	}


	List = All_Skills(startBuffs, item, 0, 1, ManipulationAllow);

	std::reverse(List.begin(), List.end());
	List.pop_back();
	
	int ListSize = List.size();
	int stepcounter, currentstep;
	int i=0;
	stepcounter = 1;
	Notes CurrentProgress;
	char ch;

	std::cout << "Prediction done, let's get to the steps.\n";
	std::cout << "\n";
	Buffs tempBuffs;

	while (i < ListSize) {
		std::cout << "Step " << stepcounter << "\n";
		CurrentProgress = List[i];

		if (!CurrentProgress.statusBuffs.Poor) {
			if (GoodCheck()) {
				std::cout << "Redoing prediction, give me a bit.\n";
				std::cout << "\n";
				tempBuffs = CurrentProgress.statusBuffs;
				tempBuffs.Good = true;
				currentstep = CurrentProgress.step;

				List = All_Skills(tempBuffs, CurrentProgress.otherInfo, CurrentProgress.Durability, CurrentProgress.step, ManipulationAllow);

				std::reverse(List.begin(), List.end());
				List.pop_back();

				ListSize = List.size();
				i = 0;

				CurrentProgress = List[i];
			}
			else if (ExcellentCheck()) {
				std::cout << "Redoing prediction, give me a bit.\n";
				std::cout << "\n";
				tempBuffs = CurrentProgress.statusBuffs;
				tempBuffs.Excellent = true;
				currentstep = CurrentProgress.step;

				List = All_Skills(tempBuffs, CurrentProgress.otherInfo, CurrentProgress.Durability, CurrentProgress.step, ManipulationAllow);

				std::reverse(List.begin(), List.end());
				List.pop_back();

				ListSize = List.size();
				i = 0;

				CurrentProgress = List[i];
			}
		}
		std::cout << "\n";

		std::cout << "Do this action:" << CurrentProgress.actions << "\n";

		std::cout << "Please press any key to continue\n";
		ch = _getch();
		std::cout << "\n";

		stepcounter++;
		i++;
	}


	return 0;
}