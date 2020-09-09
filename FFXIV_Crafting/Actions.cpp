#include <iostream>
#include <cmath>
#include <cstdint>
#include "Actions.h"
#include "Equations.h"

/*
BasicSynthesis
	Input:
		float BaseProgress
		int Veneration
		int MuscleMemory
	Output
		int Progress
	Functionality
		Increases progress. 
		Efficiency: 90% 
		Success Rate: 100% 
*/

int BasicSynthesis(float BaseProgress, int Veneration, int MuscleMemory) {
	float Efficiency = EfficencyEquation(0.9, Veneration, MuscleMemory);
	return int(floor(BaseProgress * Efficiency));
}

/*
BasicSynthesisMastered
	Input:
		float BaseProgress
		int Veneration
		int MuscleMemory
	Output
		int Progress
	Functionality
		Increases progress.
		Efficiency: 120%
		Success Rate: 100%
*/

int BasicSynthesisMastered(float BaseProgress, int Veneration, int MuscleMemory) {
	float Efficiency = EfficencyEquation(1.2, Veneration, MuscleMemory);
	return int(floor(BaseProgress * Efficiency));
}

/*
BasicTouch
	Input:
		float BaseQuality, 
		int Innovation, 
		int GreatStrides, 
		bool Poor, 
		bool Good, 
		bool Excellent
	Output
		int Quality
	Functionality
		Increases quality. 
		Efficiency: 100% 
		Success Rate: 100% 
*/

int BasicTouch(float BaseQuality, int Innovation, int GreatStrides, bool Poor, bool Good, bool Excellent) {
	float Efficiency = EfficencyEquation(1.0, Innovation, GreatStrides);
	float fC = Condition(Poor, Good, Excellent);
	return int(floor(floor(BaseQuality * fC) * Efficiency));
}

/*
HastyTouch
	Input:
		float BaseQuality,
		int Innovation,
		int GreatStrides,
		bool Poor,
		bool Good,
		bool Excellent
	Output
		int Quality
	Functionality
		Increases quality and requires no CP 
		Efficiency: 100%
		Success Rate: 60%
*/


int HastyTouch(float BaseQuality, int Innovation, int GreatStrides, bool Poor, bool Good, bool Excellent) {//Will be used for successes, and we'll find the average between success and failure
	float Efficiency = EfficencyEquation(1.0, Innovation, GreatStrides);
	float fC = Condition(Poor, Good, Excellent);
	return int(floor(floor(BaseQuality * fC) * Efficiency));
}

/*
RapidSynthesis
	Input:
		float BaseProgress
		int Veneration
		int MuscleMemory
	Output
		int Progress
	Functionality
		Increases progress and requires no CP. 
		Efficiency: 250%
		Success Rate: 60%
*/

int RapidSynthesis(float BaseProgress, int Veneration, int MuscleMemory) {
	float Efficiency = EfficencyEquation(2.5, Veneration, MuscleMemory);
	return int(floor(BaseProgress * Efficiency));
}

/*
RapidSynthesisMastered
	Input:
		float BaseProgress
		int Veneration
		int MuscleMemory
	Output
		int Progress
	Functionality
		Increases progress and requires no CP.
		Efficiency: 500%
		Success Rate: 60%
*/

int RapidSynthesisMastered(float BaseProgress, int Veneration, int MuscleMemory) {
	float Efficiency = EfficencyEquation(5, Veneration, MuscleMemory);
	return int(floor(BaseProgress * Efficiency));
}

/*
StandardTouch
	Input:
		float BaseQuality,
		int Innovation,
		int GreatStrides,
		bool Poor,
		bool Good,
		bool Excellent
	Output
		int Quality
	Functionality
		Increases quality.
		Efficiency: 125%
		Success Rate: 100%
*/

int StandardTouch(float BaseQuality, int Innovation, int GreatStrides, bool Poor, bool Good, bool Excellent) {
	float Efficiency = EfficencyEquation(1.25, Innovation, GreatStrides);
	float fC = Condition(Poor, Good, Excellent);
	return int(floor(floor(BaseQuality * fC) * Efficiency));
}



/*
BrandOfTheElements
	Input:
		float BaseProgress
		int Veneration
		int MuscleMemory
		int NameCounter
	Output
		int Progress
	Functionality
		Increases progress.
		Efficiency: 100%
		Success Rate: 100%
*/

int BrandOfTheElements(float BaseProgress, int currentProgress, int totalProgress, int NameCounter){
	float Progress;
	if (NameCounter > 0) {
		Progress = NameOfTheElements(currentProgress, totalProgress);
	}
	else {
		Progress = BaseProgress;
	}
	return Progress;
}

/*
ByregotsBlessing
	Input:
		float BaseQuality,
		int IQStacks, 
		bool Poor, 
		bool Good, 
		bool Excellent
	Output
		int Quality
	Functionality
		Increases quality. Inner Quiet effect ends upon use.  
		Efficiency: 100% plus 20% for each bonus to control granted by Inner Quiet. 
		Success Rate: 100% 
*/

int ByregotsBlessing(float BaseQuality, int IQStacks, bool Poor, bool Good, bool Excellent) {
	float Efficiency = ByregotsBlessing(IQStacks);
	float fC = Condition(Poor, Good, Excellent);
	return int(floor(floor(BaseQuality * fC) * Efficiency));
}

/*
PreciseTouch
	Input:
		float BaseQuality,
		int Innovation,
		int GreatStrides,
		bool Poor,
		bool Good,
		bool Excellent
	Output
		int Quality
	Functionality
		Increase quality. 
		Additional Effect: Increases Inner Quiet stack by one (up to 11) 
		Efficiency: 150% 
		Success Rate: 100% 
		Available only when material condition Good or Excellent. 
*/

int PreciseTouch(float BaseQuality, int Innovation, int GreatStrides, bool Poor, bool Good, bool Excellent) {
	float Efficiency = EfficencyEquation(1.50, Innovation, GreatStrides);
	float fC = Condition(Poor, Good, Excellent);
	return int(floor(floor(BaseQuality * fC) * Efficiency));
}

/*
MuscleMemory
	Input:
		float BaseProgress
	Output
		int Progress
	Functionality
		Increases progress. Efficiency: 300% 
		Success Rate: 100% 
		Additional Effect: Efficiency of your next Synthesis action is increased by 100% 
		Available only on the first step
		Additional effect is active for five steps. 
*/

int MuscleMemory(float BaseProgress) {
	float Efficiency = EfficencyEquation(3.0, 0, 0);
	return int(floor(BaseProgress * Efficiency));
}

/*
CarefulSynthesis
	Input:
		float BaseProgress
		int Veneration
		int MuscleMemory
	Output
		int Progress
	Functionality
		Increases progress.
		Efficiency: 150%
		Success Rate: 100%
*/

int CarefulSynthesis(float BaseProgress, int Veneration, int MuscleMemory) {
	float Efficiency = EfficencyEquation(1.5, Veneration, MuscleMemory);
	return int(floor(BaseProgress * Efficiency));
}

/*
PatientTouch
	Input:
		float BaseQuality,
		int Innovation,
		int GreatStrides,
		bool Poor,
		bool Good,
		bool Excellent
	Output
		int Quality
	Functionality
		Increases quality. Doubles Inner Quiet stack (up to 11) when successful, halves stack upon failure. 
		Efficiency: 100% 
		Success Rate: 50% 
*/

int PatientTouch(float BaseQuality, int Innovation, int GreatStrides, bool Poor, bool Good, bool Excellent) {//Going to pretty much treat it like Basic Touch and find the average between the two between pass and fail, since this also involves status stuff
	float Efficiency = EfficencyEquation(1.00, Innovation, GreatStrides);
	float fC = Condition(Poor, Good, Excellent);
	return int(floor(floor(BaseQuality * fC) * Efficiency));
}

/*
PrudentTouch
	Input:
		float BaseQuality,
		int Innovation,
		int GreatStrides,
		bool Poor,
		bool Good,
		bool Excellent
	Output
		int Quality
	Functionality
		Increases quality at half the durability cost.  
		Efficiency: 100% 
		Success Rate: 100% 
*/

int PrudentTouch(float BaseQuality, int Innovation, int GreatStrides, bool Poor, bool Good, bool Excellent) {//Half durability cost. I believe it is unavailable during Waste Not
	float Efficiency = EfficencyEquation(1.00, Innovation, GreatStrides);
	float fC = Condition(Poor, Good, Excellent);
	return int(floor(floor(BaseQuality * fC) * Efficiency));
}

/*
FocusedSynthesis
	Input:
		float BaseProgress
		int Veneration
		int MuscleMemory
	Output
		int Quality
	Functionality
		Increase progress. Efficiency: 200%
		Success Rate: 50%
		Combo Action: Observe
		Combo Bonus: Increase success rate to 100% 
*/

int FocusedSynthesis(float BaseProgress, int Veneration, int MuscleMemory) {
	float Efficiency = EfficencyEquation(2.0, Veneration, MuscleMemory);
	return int(floor(BaseProgress * Efficiency));
}

/*
FocusedTouch
	Input:
		float BaseQuality,
		int Innovation,
		int GreatStrides,
		bool Poor,
		bool Good,
		bool Excellent
	Output
		int Quality
	Functionality
		Increase progress. Efficiency: 150%
		Success Rate: 50%
		Combo Action: Observe
		Combo Bonus: Increase success rate to 100%
*/

int FocusedTouch(float BaseQuality, int Innovation, int GreatStrides, bool Poor, bool Good, bool Excellent) {//Going to pretty much treat it like Basic Touch and find the average between the two between pass and fail, since this also involves status stuff
	float Efficiency = EfficencyEquation(1.50, Innovation, GreatStrides);
	float fC = Condition(Poor, Good, Excellent);
	return int(floor(floor(BaseQuality * fC) * Efficiency));
}

/*
Reflect
	Input:
		float BaseQuality,
		bool Poor,
		bool Good,
		bool Excellent
	Output
		int Quality
	Functionality
		Increases quality. Increases Inner Quiet stack by three (up to 11). Available only on the first step.  
		Efficiency: 100% 
		Success Rate: 100% 
*/

int Reflect(float BaseQuality, bool Poor, bool Good, bool Excellent) {
	float Efficiency = EfficencyEquation(1.0, 0, 0);
	float fC = Condition(Poor, Good, Excellent);
	return int(floor(floor(BaseQuality * fC) * Efficiency));
}

/*
PrepatoryTouch
	Input:
		float BaseQuality,
		int Innovation,
		int GreatStrides,
		bool Poor,
		bool Good,
		bool Excellent
	Output
		int Quality
	Functionality
		Increase progress. Efficiency: 150%
		Success Rate: 50%
		Combo Action: Observe
		Combo Bonus: Increase success rate to 100%
*/

int PrepatoryTouch(float BaseQuality, int Innovation, int GreatStrides, bool Poor, bool Good, bool Excellent) {
	float Efficiency = EfficencyEquation(2.0, Innovation, GreatStrides);
	float fC = Condition(Poor, Good, Excellent);
	return int(floor(floor(BaseQuality * fC) * Efficiency));
}

/*
PrepatoryTouch
	Input:
		float BaseProgress, 
		nt CurrentDurability, 
		int WasteNot
	Output
		int Progress
	Functionality
		Increase progress at greater cost to durability. Efficiency decrease by half when durability is below durability cost.  
		Efficiency: 300% 
		Success Rate: 100% 
		Durability Cost: 20 
*/

int Groundwork(float BaseProgress, int CurrentDurability, int WasteNot) {
	float Efficiency;
	if (CurrentDurability >= 20 && WasteNot==0) {
		Efficiency = EfficencyEquation(3.0, 0, 0);
	}
	else if (CurrentDurability >= 10 && WasteNot > 0) {
		Efficiency = EfficencyEquation(3.0, 0, 0);
	}
	else {
		Efficiency = EfficencyEquation(1.5, 0, 0);
	}
	return int(floor(BaseProgress * Efficiency));
}

/*
DelicateSynthesis
	Input:
		float BaseProgress, 
		int Veneration, 
		int MuscleMemory, 
		float BaseQuality, 
		bool Poor, 
		bool Good, 
		bool Excellent
	Output
		int Progress
		int Quality
	Functionality
		Increase progress at greater cost to durability. Efficiency decrease by half when durability is below durability cost.  
		Efficiency: 300% 
		Success Rate: 100% 
		Durability Cost: 20 
*/

std::pair <int, int> DelicateSynthesis(float BaseProgress, int Veneration, int MuscleMemory, float BaseQuality, bool Poor, bool Good, bool Excellent) {
	float Efficiency = EfficencyEquation(1.0, Veneration, MuscleMemory);
	float fC = Condition(Poor, Good, Excellent);

	int Progress = int(floor(BaseProgress * Efficiency));
	int Quality = int(floor(floor(BaseQuality * fC) * Efficiency));

	std::pair <int, int> Delicate;
	Delicate.first = Progress;
	Delicate.second = Quality;

	return Delicate;
}

/*
IntensiveSynthesis
	Input:
		float BaseProgress
		int Veneration
		int MuscleMemory
	Output
		int Progress
	Functionality
		Increases progress.
		Efficiency: 300%
		Success Rate: 100%
		Available only when material is Good or Excellent.
*/

int IntensiveSynthesis(float BaseProgress, int Veneration, int MuscleMemory) {
	float Efficiency = EfficencyEquation(3.0, Veneration, MuscleMemory);
	return int(floor(BaseProgress * Efficiency));
}
