#include <iostream>
#include <iomanip>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "Actions.h"
#include "Equations.h"
#include "New_Loop.h"

/*
UpdateBuffs
	Input:
		Buffs status
	Output 
		Buffs nextStatus
	Functionality
		Updates status buffs for the next call of All_Skills
*/

Buffs updateBuffs(Buffs status) {
	if (status.Good == true) {
		status.Good = false;
	}
	else if (status.Excellent == true) {
		status.Excellent = false;
		status.Poor = true;
	}
	else if (status.Poor == true) {
		status.Poor = false;
	}

	if (status.Veneration > 0) {
		status.Veneration = status.Veneration - 1;
	}
	if (status.MuscleMemory > 0) {
		status.MuscleMemory = status.MuscleMemory - 1;
	}
	if (status.GreatStrides > 0) {
		status.GreatStrides = status.GreatStrides - 1;
	}
	if (status.Innovation > 0) {
		status.Innovation = status.Innovation - 1;
	}
	if (status.WasteNot > 0) {
		status.WasteNot = status.WasteNot - 1;
	}
	if (status.FinalAppriasal > 0) {
		status.FinalAppriasal = status.FinalAppriasal - 1;
	}
	if (status.NameOfTheElements > 0) {
		status.NameOfTheElements = status.NameOfTheElements - 1;
	}
	if (status.Manipulation > 0) {
		status.Manipulation = status.Manipulation - 1;
	}
	if (status.ObserveLast == true) {
		status.ObserveLast = false;
	}

	return status;
}

/*
UpdateBuffs
	Input:
		Buffs status
		CraftingInfo info
		int CurrentDur
		int step
		bool ManipulationAllow
	Output
		std::vector<Notes>
	Functionality
		Recursive program for creating the list of actions that should be taken for ideal results. It first sets stuff up for the next call, checks if 
		the program should be done, then checks all the actions that should be available at a player's level
*/

std::vector<Notes> All_Skills(Buffs status, CraftingInfo info, int CurrentDur, int step, bool ManipulationAllow) {
	if (info.InitiQuality > info.MaxQuality) {
		info.InitiQuality = info.MaxQuality;
	}
	if (CurrentDur < 0) {
		CurrentDur = 0;
	}


	Notes basic;
	basic.statusBuffs = status;
	basic.otherInfo = info;
	basic.Durability = CurrentDur;
	basic.steps = step;
	basic.Progress = info.InitiProgress;
	basic.Quality = info.InitiQuality;
	basic.actions = "";
	basic.step = step;

	Notes baseline = basic;

	Buffs nextStatus = updateBuffs(status);
	Buffs heldNextStatus = nextStatus;
	CraftingInfo nextInfo = info;
	CraftingInfo secondNextInfo;//In case of pass vs fail

	Notes end;
	Notes altEnd;
	Notes secondAltEnd;

	int tempInt;
	int ValueChange;

	int DurabilityCost;

	if (CurrentDur < 0) {
		CurrentDur = 0;
	}

	if (status.WasteNot > 0) {
		DurabilityCost = 5;
	}
	else {
		DurabilityCost = 10;
	}

	if (status.Manipulation > 0) {
		DurabilityCost -= 5;
	}

	std::vector<Notes> List;

	std::vector<Notes> tempVect;
	std::vector<Notes> tempVectAlt;

	if (CurrentDur >= info.Durability && info.InitiProgress < info.MaxProgress) {//If Durability runs out
		basic.Quality = -99;
		basic.actions = "Fail";

		List.push_back(basic);
		return List;
	}
	else if (info.InitiProgress >= info.MaxProgress && status.FinalAppriasal > 0) {
		info.InitiProgress = info.MaxProgress - 1;
	}
	else if (info.InitiProgress >= info.MaxProgress) {//If progress reached
		basic.actions = "Done";

		List.push_back(basic);

		return List;
	}

	float Quality = BaseQuality(info.Control, status.InnerQuiet, info.RLVL, info.LevelMod, info.stars);

	//Basic Synthesis (Which is the baseline)
	if (info.CLVL >= 31) {
		tempInt = BasicSynthesisMastered(info.BaseProgress, status.Veneration, status.MuscleMemory);
		ValueChange = tempInt;
		nextInfo.InitiProgress += tempInt;
		List = All_Skills(nextStatus, nextInfo, CurrentDur + DurabilityCost, step + 1, ManipulationAllow);
		end = List.front();
		basic.Progress += ValueChange;
		basic.actions = "Basic Syntheis";
	}
	else {
		tempInt = BasicSynthesis(info.BaseProgress, status.Veneration, status.MuscleMemory);
		ValueChange = tempInt;
		nextInfo.InitiProgress += tempInt;
		List = All_Skills(nextStatus, nextInfo, CurrentDur + DurabilityCost, step + 1, ManipulationAllow);
		end = List.front();
		basic.Progress += ValueChange;
		basic.actions = "Basic Syntheis";
	}

	//Basic Touch
	if (info.CP >= 18 && info.CLVL >= 5 && info.InitiQuality != info.MaxQuality) {
		tempInt = BasicTouch(Quality, status.Innovation, status.GreatStrides, status.Poor, status.Good, status.Excellent);
		ValueChange = tempInt;
		nextInfo = info;
		nextInfo.InitiQuality += tempInt;
		nextInfo.CP -= 18;
		nextStatus = heldNextStatus;
		if (nextStatus.InnerQuiet != 0 && nextStatus.InnerQuiet != 11) {
			nextStatus.InnerQuiet += 1;
		}
		tempVect = All_Skills(nextStatus, nextInfo, CurrentDur + DurabilityCost, step + 1, ManipulationAllow);
		altEnd = tempVect.front();

		if (end.Quality < altEnd.Quality) {
			List = tempVect;
			end = altEnd;
			basic = baseline;
			basic.Quality += ValueChange;
			basic.actions = "Basic Touch";
		}
	}

	//Master's Mend
	if (info.CP >= 88 && info.CLVL >= 7) {
		nextInfo = info;
		nextInfo.CP -= 88;
		tempVect = All_Skills(nextStatus, nextInfo, CurrentDur - 30, step + 1, ManipulationAllow);
		altEnd = tempVect.front();

		if (end.Quality < altEnd.Quality) {
			List = tempVect;
			end = altEnd;
			basic = baseline;
			basic.actions = "Master's Mend";
		}
	}

	//Need to fix up these programs that have a percentage chance for failure

	/*//Hasty Touch
	if (info.CLVL >= 9 && info.InitiQuality != info.MaxQuality) {
		tempInt = HastyTouch(Quality, status.Innovation, status.GreatStrides, status.Poor, status.Good, status.Excellent);
		ValueChange = tempInt;
		nextInfo = info;
		secondNextInfo = info;
		nextInfo.InitiQuality += tempInt;
		nextStatus = heldNextStatus;
		if (nextStatus.InnerQuiet != 0 && nextStatus.InnerQuiet != 11) {
			nextStatus.InnerQuiet += 1;
		}
		tempVect = All_Skills(nextStatus, nextInfo, CurrentDur + DurabilityCost, step + 1, ManipulationAllow);
		tempVectAlt = All_Skills(heldNextStatus, secondNextInfo, CurrentDur + DurabilityCost, step + 1, ManipulationAllow);
		altEnd = tempVect.front();
		secondAltEnd = tempVectAlt.front();
		tempInt = (0.6 * altEnd.Quality) + (0.4 * secondAltEnd.Quality);
		if (end.Quality < tempInt) {
			List = tempVect;
			end = altEnd;
			basic = baseline;
			basic.Quality += ValueChange;
			basic.actions = "Hasty Touch";
		}
	}*/

	/*//Rapid Synthesis
	if (info.CLVL >= 9) {
		tempInt = RapidSynthesis(info.BaseProgress, status.Veneration, status.MuscleMemory);
		ValueChange = tempInt;
		nextInfo = info;
		nextStatus = heldNextStatus;
		nextInfo.InitiProgress += tempInt;
		secondNextInfo = info;
		tempVect = All_Skills(nextStatus, nextInfo, CurrentDur + DurabilityCost, step + 1, ManipulationAllow);
		tempVectAlt = All_Skills(nextStatus, secondNextInfo, CurrentDur + DurabilityCost, step + 1, ManipulationAllow);
		altEnd = tempVect.front();
		secondAltEnd = tempVectAlt.front();
		tempInt = (0.6 * altEnd.Quality) + (0.4 * secondAltEnd.Quality);
		if (end.Quality < tempInt) {
			List = tempVect;
			end = altEnd;
			basic = baseline;
			basic.Progress += ValueChange;
			basic.actions = "Rapid Synthesis";
		}
	}
	else if (info.CLVL >= 63) {
		tempInt = RapidSynthesisMastered(info.BaseProgress, status.Veneration, status.MuscleMemory);
		ValueChange = tempInt;
		nextInfo = info;
		nextStatus = heldNextStatus;
		nextInfo.InitiProgress += tempInt;
		secondNextInfo = info;
		tempVect = All_Skills(nextStatus, nextInfo, CurrentDur + DurabilityCost, step + 1, ManipulationAllow);
		tempVectAlt = All_Skills(nextStatus, secondNextInfo, CurrentDur + DurabilityCost, step + 1, ManipulationAllow);
		altEnd = tempVect.front();
		secondAltEnd = tempVectAlt.front();
		tempInt = (0.6 * altEnd.Quality) + (0.4 * secondAltEnd.Quality);
		if (end.Quality < tempInt) {
			List = tempVect;
			end = altEnd;
			basic = baseline;
			basic.Progress += ValueChange;
			basic.actions = "Rapid Synthesis";
		}
	}*/

	//Inner Quiet
	if (info.CP >= 18 && status.InnerQuiet == 0 && info.CLVL >= 11 && info.InitiQuality != info.MaxQuality) {
		nextInfo = info;
		nextStatus = heldNextStatus;
		nextStatus.InnerQuiet = 1;
		nextInfo.CP -= 18;
		tempVect = All_Skills(nextStatus, nextInfo, CurrentDur + DurabilityCost, step + 1, ManipulationAllow);
		altEnd = tempVect.front();
		if (end.Quality < altEnd.Quality) {
			List = tempVect;
			end = altEnd;
			basic = baseline;
			basic.actions = "Inner Quiet";
		}
	}

	//Observe
	if (info.CP >= 7 && info.CLVL >= 13) {
		nextInfo = info;
		nextStatus = heldNextStatus;
		nextInfo.CP -= 7;
		nextStatus.ObserveLast = true;
		tempVect = All_Skills(nextStatus, nextInfo, CurrentDur, step + 1, ManipulationAllow);
		altEnd = tempVect.front();
		if (end.Quality < altEnd.Quality) {
			List = tempVect;
			end = altEnd;
			basic = baseline;
			basic.actions = "Observe";
		}
	}

	//Tricks of the Trade
	if ((status.Good || status.Excellent) && info.CLVL >= 13) {
		nextInfo = info;
		nextStatus = heldNextStatus;
		nextInfo.CP += 20;
		tempVect = All_Skills(nextStatus, nextInfo, CurrentDur, step + 1, ManipulationAllow);
		altEnd = tempVect.front();
		if (end.Quality < altEnd.Quality) {
			List = tempVect;
			end = altEnd;
			basic = baseline;
			basic.actions = "Tricks of the Trade";
		}
	}

	//Waste Not
	if (info.CP >= 56 && info.CLVL >= 15) {
		nextInfo = info;
		nextStatus = heldNextStatus;
		nextStatus.WasteNot = 4;
		nextInfo.CP -= 56;
		tempVect = All_Skills(nextStatus, nextInfo, CurrentDur + DurabilityCost, step + 1, ManipulationAllow);
		altEnd = tempVect.front();
		if (end.Quality < altEnd.Quality) {
			List = tempVect;
			end = altEnd;
			basic = baseline;
			basic.actions = "Waste Not";
		}
	}

	//Veneration
	if (info.CP >= 18 && info.CLVL >= 15) {
		nextInfo = info;
		nextStatus = heldNextStatus;
		nextStatus.Veneration = 4;
		nextInfo.CP -= 18;
		tempVect = All_Skills(nextStatus, nextInfo, CurrentDur + DurabilityCost, step + 1, ManipulationAllow);
		altEnd = tempVect.front();
		if (end.Quality < altEnd.Quality) {
			List = tempVect;
			end = altEnd;
			basic = baseline;
			basic.actions = "Veneration";
		}
	}

	//Standard Touch
	if (info.CP >= 32 && info.CLVL >= 18 && info.InitiQuality != info.MaxQuality) {
		tempInt = StandardTouch(Quality, status.Innovation, status.GreatStrides, status.Poor, status.Good, status.Excellent);
		ValueChange = tempInt;
		nextInfo = info;
		nextInfo.InitiQuality += tempInt;
		nextInfo.CP -= 32;
		nextStatus = heldNextStatus;
		if (nextStatus.InnerQuiet != 0 && nextStatus.InnerQuiet != 11) {
			nextStatus.InnerQuiet += 1;
		}
		tempVect = All_Skills(nextStatus, nextInfo, CurrentDur + DurabilityCost, step + 1, ManipulationAllow);
		altEnd = tempVect.front();

		if (end.Quality < altEnd.Quality) {
			List = tempVect;
			end = altEnd;
			basic = baseline;
			basic.Quality += ValueChange;
			basic.actions = "Standard Touch";
		}
	}

	//Great Strides
	if (info.CP >= 32 && info.CLVL >= 21 && info.InitiQuality != info.MaxQuality) {
		nextInfo = info;
		nextStatus = heldNextStatus;
		nextStatus.GreatStrides = 3;
		nextInfo.CP -= 32;
		tempVect = All_Skills(nextStatus, nextInfo, CurrentDur + DurabilityCost, step + 1, ManipulationAllow);
		altEnd = tempVect.front();
		if (end.Quality < altEnd.Quality) {
			List = tempVect;
			end = altEnd;
			basic = baseline;
			basic.actions = "Great Strides";
		}
	}

	//Innovation
	if (info.CP >= 18 && info.CLVL >= 26 && info.InitiQuality != info.MaxQuality) {
		nextInfo = info;
		nextStatus = heldNextStatus;
		nextStatus.Innovation = 4;
		nextInfo.CP -= 18;
		tempVect = All_Skills(nextStatus, nextInfo, CurrentDur + DurabilityCost, step + 1, ManipulationAllow);
		altEnd = tempVect.front();
		if (end.Quality < altEnd.Quality) {
			List = tempVect;
			end = altEnd;
			basic = baseline;
			basic.actions = "Innovation";
		}
	}

	//Name of the Elements
	if (info.CP >= 30 && status.Nameless == false && info.CLVL >= 37) {
		nextInfo = info;
		nextStatus = heldNextStatus;
		nextStatus.NameOfTheElements = 3;
		nextStatus.Nameless = true;
		nextInfo.CP -= 30;
		tempVect = All_Skills(nextStatus, nextInfo, CurrentDur + DurabilityCost, step + 1, ManipulationAllow);
		altEnd = tempVect.front();
		if (end.Quality < altEnd.Quality) {
			List = tempVect;
			end = altEnd;
			basic = baseline;
			basic.actions = "Name of the Elements";
		}
	}

	//Brand of the Elements
	if (info.CP >= 6 && info.CLVL >= 37) {
		tempInt = BrandOfTheElements(info.BaseProgress, info.InitiProgress, info.MaxProgress, status.NameOfTheElements);
		ValueChange = tempInt;
		nextInfo = info;
		nextStatus = heldNextStatus;
		nextInfo.InitiProgress += tempInt;
		nextInfo.CP -= 6;
		tempVect = All_Skills(nextStatus, nextInfo, CurrentDur + DurabilityCost, step + 1, ManipulationAllow);
		altEnd = tempVect.front();

		if (end.Quality < altEnd.Quality) {
			List = tempVect;
			end = altEnd;
			basic = baseline;
			basic.Progress += ValueChange;
			basic.actions = "Brand of the Elements";
		}
	}

	//Final Appraisal
	if (info.CP >= 1 && info.CLVL >= 42) {
		nextInfo = info;
		nextStatus = heldNextStatus;
		nextStatus.FinalAppriasal = 5;
		nextInfo.CP -= 1;
		tempVect = All_Skills(nextStatus, nextInfo, CurrentDur + DurabilityCost, step + 1, ManipulationAllow);
		altEnd = tempVect.front();
		if (end.Quality < altEnd.Quality) {
			List = tempVect;
			end = altEnd;
			basic = baseline;
			basic.actions = "Final Appraisal";
		}
	}

	//Waste Not II
	if (info.CP >= 98 && info.CLVL >= 47) {
		nextInfo = info;
		nextStatus = heldNextStatus;
		nextStatus.WasteNot = 8;
		nextInfo.CP -= 98;
		tempVect = All_Skills(nextStatus, nextInfo, CurrentDur + DurabilityCost, step + 1, ManipulationAllow);
		altEnd = tempVect.front();
		if (end.Quality < altEnd.Quality) {
			List = tempVect;
			end = altEnd;
			basic = baseline;
			basic.actions = "Waste Not II";
		}
	}

	//Byregot's Blessing
	if (info.CP >= 24 && status.InnerQuiet >= 2 && info.CLVL >= 50 && info.InitiQuality != info.MaxQuality) {
		tempInt = ByregotsBlessing(Quality, status.InnerQuiet, status.Poor, status.Good, status.Excellent);
		ValueChange = tempInt;
		nextInfo = info;
		nextInfo.InitiQuality += tempInt;
		nextInfo.CP -= 24;
		nextStatus = heldNextStatus;
		nextStatus.InnerQuiet = 0;
		tempVect = All_Skills(nextStatus, nextInfo, CurrentDur + DurabilityCost, step + 1, ManipulationAllow);
		altEnd = tempVect.front();

		if (end.Quality < altEnd.Quality) {
			List = tempVect;
			end = altEnd;
			basic = baseline;
			basic.Quality += ValueChange;
			basic.actions = "Byregot's Blessing";
		}
	}

	//Precise Touch
	if (info.CP >= 18 && (status.Good || status.Excellent) && info.CLVL >= 53 && info.InitiQuality != info.MaxQuality) {
		tempInt = PreciseTouch(Quality, status.Innovation, status.GreatStrides, status.Poor, status.Good, status.Excellent);
		ValueChange = tempInt;
		nextInfo = info;
		nextInfo.InitiQuality += tempInt;
		nextInfo.CP -= 18;
		nextStatus = heldNextStatus;
		if (nextStatus.InnerQuiet != 0 && nextStatus.InnerQuiet != 11) {
			nextStatus.InnerQuiet += 2;
		}
		else if (nextStatus.InnerQuiet == 0 || nextStatus.InnerQuiet == 10) {
			nextStatus.InnerQuiet += 1;
		}
		tempVect = All_Skills(nextStatus, nextInfo, CurrentDur + DurabilityCost, step + 1, ManipulationAllow);
		altEnd = tempVect.front();

		if (end.Quality < altEnd.Quality) {
			List = tempVect;
			end = altEnd;
			basic = baseline;
			basic.Quality += ValueChange;
			basic.actions = "Precise Touch";
		}
	}

	//Muscle Memory
	if (info.CP >= 6 && step == 1 && info.CLVL >= 54) {
		tempInt = MuscleMemory(info.BaseProgress);
		ValueChange = tempInt;
		nextInfo = info;
		nextInfo.InitiProgress += tempInt;
		nextInfo.CP -= 6;
		nextStatus = heldNextStatus;
		nextStatus.MuscleMemory = 5;
		tempVect = All_Skills(nextStatus, nextInfo, CurrentDur + DurabilityCost, step + 1, ManipulationAllow);
		altEnd = tempVect.front();

		if (end.Quality < altEnd.Quality) {
			List = tempVect;
			end = altEnd;
			basic = baseline;
			basic.Progress += ValueChange;
			basic.actions = "Muscle Memory";
		}
	}

	//Careful Observation
	if (status.CarefulObservation > 0 && info.CLVL >= 55) {
		nextInfo = info;
		nextStatus = status;
		if (nextStatus.Good) {
			nextStatus.Good = false;
		}
		else if (nextStatus.Excellent) {
			nextStatus.Excellent = false;
			nextStatus.Poor = true;
		}
		else if (nextStatus.Poor) {
			nextStatus.Poor = false;
		}
		nextStatus.CarefulObservation -= 1;

		tempVect = All_Skills(nextStatus, nextInfo, CurrentDur, step, ManipulationAllow);
		if (end.Quality < altEnd.Quality) {
			List = tempVect;
			end = altEnd;
			basic = baseline;
			basic.actions = "Careful Observation";
		}
	}

	//Careful Synthesis
	if (info.CP >= 7 && info.CLVL >= 62) {
		tempInt = CarefulSynthesis(info.BaseProgress, status.Veneration, status.MuscleMemory);
		ValueChange = tempInt;
		nextInfo = info;
		nextInfo.InitiProgress += tempInt;
		nextInfo.CP -= 7;
		nextStatus = heldNextStatus;
		tempVect = All_Skills(nextStatus, nextInfo, CurrentDur + DurabilityCost, step + 1, ManipulationAllow);
		altEnd = tempVect.front();

		if (end.Quality < altEnd.Quality) {
			List = tempVect;
			end = altEnd;
			basic = baseline;
			basic.Progress += ValueChange;
			basic.actions = "Careful Synthesis";
		}
	}

	/*
	//Patient Touch
	if (info.CP >= 6 && status.InnerQuiet > 0 && info.CLVL >= 64 && info.InitiQuality != info.MaxQuality) {
		//success
		tempInt = PatientTouch(Quality, status.Innovation, status.GreatStrides, status.Poor, status.Good, status.Excellent);
		ValueChange = tempInt;
		nextInfo = info;
		nextStatus = heldNextStatus;
		nextInfo.InitiQuality += tempInt;
		nextInfo.CP -= 6;
		nextStatus = heldNextStatus;
		nextStatus.InnerQuiet = nextStatus.InnerQuiet * 2;
		tempVect = All_Skills(nextStatus, nextInfo, CurrentDur + DurabilityCost, step + 1, ManipulationAllow);
		altEnd = tempVect.front();

		//failure
		nextInfo.InitiQuality = info.InitiQuality;
		nextStatus = heldNextStatus;
		tempInt = nextStatus.InnerQuiet % 2;
		nextStatus.InnerQuiet = nextStatus.InnerQuiet / 2;
		if (tempInt != 0) {
			nextStatus.InnerQuiet -= 1;
		}
		tempVectAlt = All_Skills(nextStatus, nextInfo, CurrentDur + DurabilityCost, step + 1, ManipulationAllow);
		secondAltEnd = tempVectAlt.front();

		tempInt = (0.5 * altEnd.Quality) + (0.5 * secondAltEnd.Quality);
		if (end.Quality < tempInt) {
			List = tempVect;
			end = altEnd;
			basic = baseline;
			basic.Quality += ValueChange;
			basic.actions = "Patient Touch";
		}
	}
	*/

	//Manipulation
	if (info.CP >= 96 && info.CLVL >= 65 && ManipulationAllow) {
		nextInfo = info;
		nextStatus = heldNextStatus;
		nextStatus.Manipulation = 8;
		nextInfo.CP -= 96;
		tempVect = All_Skills(nextStatus, nextInfo, CurrentDur + DurabilityCost, step + 1, ManipulationAllow);
		altEnd = tempVect.front();
		if (end.Quality < altEnd.Quality) {
			List = tempVect;
			end = altEnd;
			basic = baseline;
			basic.actions = "Manipulation";
		}
	}

	//Prudent Touch
	if (info.CP >= 25 && status.WasteNot == 0 && info.CLVL >= 66 && info.InitiQuality != info.MaxQuality) {
		tempInt = PrudentTouch(Quality, status.Innovation, status.GreatStrides, status.Poor, status.Good, status.Excellent);
		ValueChange = tempInt;
		nextInfo = info;
		nextInfo.InitiQuality += tempInt;
		nextInfo.CP -= 25;
		nextStatus = heldNextStatus;
		if (nextStatus.InnerQuiet != 0 && nextStatus.InnerQuiet != 11) {
			nextStatus.InnerQuiet += 1;
		}
		tempVect = All_Skills(nextStatus, nextInfo, CurrentDur + DurabilityCost - 5, step + 1, ManipulationAllow);
		altEnd = tempVect.front();

		if (end.Quality < altEnd.Quality) {
			List = tempVect;
			end = altEnd;
			basic = baseline;
			basic.Quality += ValueChange;
			basic.actions = "Standard Touch";
		}
	}

	/*
	//Focused Synthesis
	if (info.CP >= 5 && info.CLVL >= 67) {
		tempInt = FocusedSynthesis(info.BaseProgress, status.Veneration, status.MuscleMemory);
		ValueChange = tempInt;
		nextInfo = info;
		nextInfo.CP -= 5;
		nextStatus = heldNextStatus;
		nextInfo.InitiProgress += ValueChange;
		tempVect = All_Skills(nextStatus, nextInfo, CurrentDur + DurabilityCost, step + 1, ManipulationAllow);
		altEnd = tempVect.front();

		secondNextInfo = info;
		secondNextInfo.CP -= 5;
		nextStatus = heldNextStatus;
		tempVectAlt = All_Skills(nextStatus, secondNextInfo, CurrentDur + DurabilityCost, step + 1, ManipulationAllow);
		secondAltEnd = tempVectAlt.front();

		if (status.ObserveLast) {
			tempInt = altEnd.Progress;
		}
		else {
			tempInt = (0.5 * altEnd.Progress) + (0.5 * secondAltEnd.Progress);
		}

		if (end.Quality < tempInt) {
			List = tempVect;
			end = altEnd;
			basic = baseline;
			basic.Progress += ValueChange;
			basic.actions = "Focused Synthesis";
		}
	}

	//Focused Touch
	if (info.CP >= 18 && info.CLVL >= 68 && info.InitiQuality != info.MaxQuality) {
		tempInt = FocusedTouch(Quality, status.Innovation, status.GreatStrides, status.Poor, status.Good, status.Excellent);
		ValueChange = tempInt;
		nextInfo = info;
		nextInfo.CP -= 18;
		nextStatus = heldNextStatus;
		if (nextStatus.InnerQuiet != 0 && nextStatus.InnerQuiet != 11) {
			nextStatus.InnerQuiet += 1;
		}
		nextInfo.InitiQuality += ValueChange;
		tempVect = All_Skills(nextStatus, nextInfo, CurrentDur + DurabilityCost, step + 1, ManipulationAllow);
		altEnd = tempVect.front();


		secondNextInfo = info;
		secondNextInfo.CP -= 18;
		nextStatus = heldNextStatus;
		tempVectAlt = All_Skills(nextStatus, secondNextInfo, CurrentDur + DurabilityCost, step + 1, ManipulationAllow);
		secondAltEnd = tempVectAlt.front();

		if (status.ObserveLast) {
			tempInt = altEnd.Quality;
		}
		else {
			tempInt = (0.5 * altEnd.Quality) + (0.5 * secondAltEnd.Quality);
		}

		if (end.Quality < tempInt) {
			List = tempVect;
			end = altEnd;
			basic = baseline;
			basic.Quality += ValueChange;
			basic.actions = "Focused Touch";
		}
	}
	*/

	//Reflect
	if (info.CP >= 24 && step == 1 && info.CLVL >= 69 && info.InitiQuality != info.MaxQuality) {
		ValueChange = Reflect(Quality, status.Poor, status.Good, status.Excellent);
		nextInfo = info;
		nextInfo.CP -= 24;
		nextStatus = heldNextStatus;
		if (nextStatus.InnerQuiet <= 8) {
			nextStatus.InnerQuiet += 3;
		}
		else if (nextStatus.InnerQuiet == 9) {
			nextStatus.InnerQuiet += 2;
		}
		else if (nextStatus.InnerQuiet == 10) {
			nextStatus.InnerQuiet += 1;
		}
		nextStatus.InnerQuiet += 3;
		nextInfo.InitiQuality += ValueChange;
		tempVect = All_Skills(nextStatus, nextInfo, CurrentDur + DurabilityCost, step + 1, ManipulationAllow);
		altEnd = tempVect.front();

		if (end.Quality < altEnd.Quality) {
			List = tempVect;
			end = altEnd;
			basic = baseline;
			basic.Quality += ValueChange;
			basic.actions = "Reflect";
		}
	}

	//Prepatory Touch
	if (info.CP >= 40 && info.CLVL >= 71 && info.InitiQuality != info.MaxQuality) {
		tempInt = PrepatoryTouch(Quality, status.Innovation, status.GreatStrides, status.Poor, status.Good, status.Excellent);
		ValueChange = tempInt;
		nextInfo = info;
		nextInfo.InitiQuality += tempInt;
		nextInfo.CP -= 40;
		nextStatus = heldNextStatus;
		if (nextStatus.InnerQuiet != 0 && nextStatus.InnerQuiet != 11) {
			nextStatus.InnerQuiet += 2;
		}
		else if (nextStatus.InnerQuiet == 0 || nextStatus.InnerQuiet == 10) {
			nextStatus.InnerQuiet += 1;
		}
		tempVect = All_Skills(nextStatus, nextInfo, CurrentDur + (2 * DurabilityCost), step + 1, ManipulationAllow);
		altEnd = tempVect.front();

		if (end.Quality < altEnd.Quality) {
			List = tempVect;
			end = altEnd;
			basic = baseline;
			basic.Quality += ValueChange;
			basic.actions = "Prepatory Touch";
		}
	}

	//Groundwork
	if (info.CP >= 18 && info.CLVL >= 72) {
		ValueChange = Groundwork(info.BaseProgress, info.Durability - CurrentDur, status.WasteNot);
		nextInfo = info;
		nextInfo.CP -= 18;
		nextStatus = heldNextStatus;
		nextInfo.InitiProgress += ValueChange;
		tempVect = All_Skills(nextStatus, nextInfo, CurrentDur + (2 * DurabilityCost), step + 1, ManipulationAllow);
		altEnd = tempVect.front();

		if (end.Quality < altEnd.Quality) {
			List = tempVect;
			end = altEnd;
			basic = baseline;
			basic.Progress += ValueChange;
			basic.actions = "Groundwork";
		}
	}

	//Delicate Synthesis
	if (info.CP >= 32 && info.CLVL >= 76) {
		std::pair <int, int> deli = DelicateSynthesis(info.BaseProgress, status.Veneration, status.MuscleMemory, Quality, status.Poor, status.Good, status.Excellent);//<Progress,Quality>
		nextInfo = info;
		nextInfo.InitiProgress += deli.first;
		nextInfo.InitiQuality += deli.second;
		nextInfo.CP -= 32;
		nextStatus = heldNextStatus;
		if (nextStatus.InnerQuiet != 0 && nextStatus.InnerQuiet != 11) {
			nextStatus.InnerQuiet += 1;
		}
		tempVect = All_Skills(nextStatus, nextInfo, CurrentDur + DurabilityCost, step + 1, ManipulationAllow);
		altEnd = tempVect.front();

		if (end.Quality < altEnd.Quality) {
			List = tempVect;
			end = altEnd;
			basic = baseline;
			basic.Progress += deli.first;
			basic.Quality += deli.second;
			basic.actions = "Delicate Synthesis";
		}
	}

	//Intenseive Synthesis
	if (info.CP >= 78 && (status.Good || status.Excellent) && info.CLVL >= 78) {
		ValueChange = IntensiveSynthesis(info.BaseProgress, status.Veneration, status.MuscleMemory);
			nextInfo = info;
			nextInfo.InitiProgress += ValueChange;
			nextInfo.CP -= 78;
			nextStatus = heldNextStatus;
			tempVect = All_Skills(nextStatus, nextInfo, CurrentDur + DurabilityCost, step + 1, ManipulationAllow);
			altEnd = tempVect.front();

			if (end.Quality < altEnd.Quality) {
				List = tempVect;
					end = altEnd;
				basic = baseline;
				basic.Progress += ValueChange;
				basic.actions = "Careful Synthesis";
			}
	}

	//Trained Eye
	if (info.CP >= 250 && (info.CLVL - info.RLVL) >= 10 && info.CLVL == 80) {
		ValueChange = info.MaxQuality;
		nextInfo = info;
		nextInfo.InitiQuality += ValueChange;
		nextInfo.CP -= 250;
		nextStatus = heldNextStatus;
		tempVect = All_Skills(nextStatus, nextInfo, CurrentDur + DurabilityCost, step + 1, ManipulationAllow);
		altEnd = tempVect.front();

		if (end.Quality < altEnd.Quality) {
			List = tempVect;
			end = altEnd;
			basic = baseline;
			basic.Quality += ValueChange;
			basic.actions = "Trained Eye";
		}
	}

	if (info.InitiQuality > info.MaxQuality) {
		info.InitiQuality = info.MaxQuality;
	}

	//std::cout << "Step: " << step << " Progress: " << nextInfo.InitiProgress << " Quality:" << nextInfo.InitiQuality << "\n";

	List.push_back(basic);
	return List;
}