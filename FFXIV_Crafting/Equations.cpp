#include <iostream>
#include <cmath>
#include <cstdint>
#include "Equations.h"

//Based on this: https://docs.google.com/document/d/1Da48dDVPB7N4ignxGeo0UeJ_6R0kQRqzLUH-TkpSQRc/edit#

/*
FindLevelMod
	Input:
		int CLVL, 
		int RLVL
	Output
		int LevelMod
	Functionality
		Returns level difference, used for LevelMod
*/

int FindLevelMod(int CLVL, int RLVL) {
	int difference = CLVL - RLVL;
	if (difference > 20) {
		difference = 20;
	}
	else if (difference < -39) {
		difference = -39;
	}
	return difference;
}

/*
BaseProgress
	Input:
		int Craftsmanship, 
		int RLVL, 
		int LevelMod, 
		int stars
	Output
		float BaseProgress
	Functionality
		Finds the value that's used for standard progress increases
*/

float BaseProgress(int Craftsmanship, int RLVL, int LevelMod, int stars) {//Will be constant throughout the entire thing, excluding any changes to effiecency
	float P1 = (float(Craftsmanship) * 21 / 100) + 2;

	int Recipe1To49[49] = {22, 22, 22, 22, 50, 50, 50, 59, 59, 59, 67, 67, 67, 67, 67, 78, 78, 78, 82, 94, 94, 94, 99, 99, 99, 99, 99, 106, 106, 106, 121, 121, 121, 129, 129, 129, 129, 129, 136, 136, 136, 150, 150, 150, 150, 150, 161, 161, 161};
	int Recipe50[5] = {176, 325, 325, 391, 451};
	int Recipe51to59[9] = {468, 502, 519, 529, 539, 550, 560, 570, 580};
	int Recipe60[5] = {587, 620, 718, 870, 995};
	int Recipe61to69[9] = {1006, 1027, 1037, 1044, 1050, 1056, 1063, 1069, 1075};
	int Recipe70[5] = {1079, 1100, 1320, 1500, 1650};
	int Recipe71to79[9] = { 1320, 1388, 1457, 1498, 1539, 1580, 1621, 1662, 1702 };
	int Recipe80[4] = { 1866, 2000, 2140, 2480 };

	int RecipeValue = 0;
	if (RLVL >= 1 && RLVL <= 49) {
		RecipeValue = Recipe1To49[RLVL - 1];
	}
	else if (RLVL == 50) {
		RecipeValue = Recipe50[stars];
	}
	else if (RLVL >= 51 && RLVL <= 59) {
		RecipeValue = Recipe51to59[RLVL - 51];
	}
	else if (RLVL == 60) {
		RecipeValue = Recipe60[stars];
	}
	else if (RLVL >= 61 && RLVL <= 69) {
		RecipeValue = Recipe61to69[RLVL - 61];
	}
	else if (RLVL == 70) {
		RecipeValue = Recipe70[stars];
	}
	else if (RLVL >= 71 && RLVL <= 79) {
		RecipeValue = Recipe71to79[RLVL - 71];
	}
	else if (RLVL == 80) {
		RecipeValue = Recipe80[stars];
	}

	float P2 = (P1 * (float(Craftsmanship) + 10000)) / (float(RecipeValue) + 10000);

	int LevelModTable[51] = { 80, 82, 84, 86, 88, 90, 92, 94, 96, 98, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 105, 110, 115, 120, 125, 127, 129, 131, 133, 135, 137, 139, 141, 143, 145, 147, 147, 148, 149, 150 };
	
	float LevelModValue = float(LevelModTable[LevelMod]);

	float P3 = (P2 * LevelModValue) / 100;

	return floor(P3);//Progress is determiend by flooring P3 and multipying it by the efficeincy
}

/*
IQ
	Input:
		int Control, 
		int IQStacks
	Output
		float IQ
	Functionality
		Determines value of IQ modifier
*/

float IQ(int Control, int IQStacks) {
	float tempStack;
	if (IQStacks > 0) {
		tempStack = float(IQStacks);
	}
	else {
		tempStack = 1;
	}
	float IQ = float(Control) + (float(Control) * ((tempStack - 1) * 20 / 100));
	return IQ;
}

/*
BaseQuality
	Input:
		int Control, 
		int IQStacks,
		int RLVL, 
		int LevelMod, 
		int stars
	Output
		float BaseQuality
	Functionality
		Finds the value that's used for standard quality increases
*/

float BaseQuality(int Control, int IQStacks, int RLVL, int LevelMod, int stars) {//Will need to be rerun each time IQ gets updated
	float IQValue = IQ(Control, IQStacks);

	float Q1 = (IQValue * 35 / 100) + 35;

	int Recipe1To49[49] = {11, 11, 11, 11, 25, 25, 25, 29, 29, 29, 33, 33, 33, 33, 33, 39, 39, 39, 41, 47, 47, 47, 49, 49, 49, 49, 49, 53, 53, 53, 60, 60, 60, 64, 64, 64, 64, 64, 68, 68, 68, 75, 75, 75, 75, 75, 80, 80, 80};
	int Recipe50[5] = {88, 325, 325, 374, 407};
	int Recipe51to59[9] = {426, 462, 480, 491, 502, 513, 524, 535, 546};
	int Recipe60[5] = {553, 589, 695, 835, 955};
	int Recipe61to69[9] = {968, 993, 1005, 1013, 1020, 1028, 1035, 1043, 1050};
	int Recipe70[5] = {1055, 1080, 1220, 1350, 1600};
	int Recipe71to79[9] = {1220, 1284, 1348, 1387, 1425, 1464, 1502, 1541, 1579};
	int Recipe80[4] = {1733, 1860, 1990, 2195};

	int RecipeValue = 0;
	if (RLVL >= 1 && RLVL <= 49) {
		RecipeValue = Recipe1To49[RLVL - 1];
	}
	else if (RLVL == 50) {
		RecipeValue = Recipe50[stars];
	}
	else if (RLVL >= 51 && RLVL <= 59) {
		RecipeValue = Recipe51to59[RLVL - 51];
	}
	else if (RLVL == 60) {
		RecipeValue = Recipe60[stars];
	}
	else if (RLVL >= 61 && RLVL <= 69) {
		RecipeValue = Recipe61to69[RLVL - 61];
	}
	else if (RLVL == 70) {
		RecipeValue = Recipe70[stars];
	}
	else if (RLVL >= 71 && RLVL <= 79) {
		RecipeValue = Recipe71to79[RLVL - 71];
	}
	else if (RLVL == 80) {
		RecipeValue = Recipe80[stars];
	}

	float Q2;

	Q2 = (Q1 * (IQValue + 10000)) / (RecipeValue + 10000);

	int LevelModTable[51] = { 60, 64, 68, 72, 76, 80, 84, 88, 92, 96, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100 };

	float LevelModValue = float(LevelModTable[LevelMod]);
	
	float Q3 = (Q2 * LevelModValue) / 100;
	return Q3;//Q3 used for the end equation
}

/*
Condition
	Input:
		bool Poor, 
		bool Good, 
		bool Excellent
	Output
		float Condition
	Functionality
		Determines value of Condition modifier
*/

float Condition(bool Poor, bool Good, bool Excellent) {
	float C_Value;
	if (Poor) {
		C_Value = 50;
	}
	else if (Good) {
		C_Value = 150;
	}
	else if (Excellent) {
		C_Value = 400;
	}
	else {
		C_Value = 100;
	}

	return (C_Value / 100);
}

/*
EfficencyEquation
	Input:
		float Efficiency, 
		int Veneration_Innovation,
		int GreatStrides_MuscleMemory
	Output
		float Efficency
	Functionality
		Determines bonuses to efficency
*/

float EfficencyEquation(float Efficiency, int Veneration_Innovation, int GreatStrides_MuscleMemory) {
	int Fifty_Bonus, Hundred_Bonus;

	if (Veneration_Innovation > 0) {
		Fifty_Bonus = 50;
	}
	else {
		Fifty_Bonus = 0;
	}

	if (GreatStrides_MuscleMemory > 0) {
		Hundred_Bonus = 100;
	}
	else {
		Hundred_Bonus = 0;
	}

	return (float(Efficiency) * ((100 + Fifty_Bonus + Hundred_Bonus) / 100));
}

/*
ByregotsBlessing
	Input:
		int IQStacks
	Output
		float Efficency
	Functionality
		Determines effiency for Byregot's Blessing
*/

float ByregotsBlessing(int IQStacks) {
	float tempStack;
	if (IQStacks > 0) {
		tempStack = float(IQStacks);
	}
	else {
		tempStack = 1;
	}

	float Effiency = 100 + ((tempStack - 1) * 20);
	return Effiency;
}
/*
NameOfTheElements
	Input:
		int currentProgress, 
		int totalProgress
	Output
		float Efficency
	Functionality
		Determines effiency for Brand of the elements
*/

float NameOfTheElements(int currentProgress, int totalProgress) {
	float Efficency = EfficencyEquation(1, 0, 0);
	float Modifier = 1 - (float(currentProgress) / float(totalProgress));
	return (Efficency + (2 * ceil(Modifier)));
}