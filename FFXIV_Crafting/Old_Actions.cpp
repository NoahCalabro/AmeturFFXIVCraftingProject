#include <iostream>
#include "Actions.h"

using namespace std;



float ProgressEquation(int Craftsmanship) {//Get the progress value from craftsmanship

	return 0;
}

float QualityEquation(int Control, int InnerQuiet) {//Get the quality value from control
	return 0;
}

int BasicSynthesis(int Craftsmanship, int Veneration) {
	float Progress = ProgressEquation(Craftsmanship);

	float V_Bonus;//tells us the bonus to include for Veneration
	if (Veneration > 0) {
		V_Bonus = 0.5;
	}
	else {
		V_Bonus = 0;
	}

	int integer = int((1 + V_Bonus) * (0.9 * Progress));
	return integer;
}

int BasicSynthesisMastered(int Craftsmanship, int Veneration, int MuscleMemory) {
	float Progress = ProgressEquation(Craftsmanship);
	
	float  V_Bonus;//tells us the bonus to include for Veneration
	if (Veneration > 0) {
		V_Bonus = 0.5;
	}
	else {
		V_Bonus = 0;
	}

	float M_Bonus;//tells us the bonus to include for Veneration
	if (MuscleMemory > 0) {
		M_Bonus = 1;
	}
	else {
		M_Bonus = 0;
	}

	int integer = int((1 + V_Bonus + M_Bonus) * (1.2 * Progress));
	return integer;

}

int BasicTouch(int Control, int InnerQuiet, int GreatStrides, int Innovation, bool Good, bool Excellent) {
	float Quality = QualityEquation(Control, InnerQuiet);

	float GS_Bonus;//Bonus from Great Strides
	if (GreatStrides > 0) {
		GS_Bonus = 1;
	}
	else {
		GS_Bonus = 0;
	}
	float I_Bonus;
	if (Innovation > 0) {
		I_Bonus = 0.5;
	}
	else {
		I_Bonus = 0;
	}

	float C_Bonus;//tells us the bonus from condition
	if (Good) {
		C_Bonus = 1.5;
	}
	else if (Excellent) {
		C_Bonus = 4;
	}
	else {
		C_Bonus = 1;
	}

	int integer = int((C_Bonus) * (1 + GS_Bonus + I_Bonus) * Quality);
	return integer;
}

//Master's Mend will be done in the loop

int HastyTouch(int Control, int InnerQuiet, int GreatStrides, int Innovation, bool Good, bool Excellent) {//Will be for cases of success. Otherwise it doesn't happen
	float Quality = QualityEquation(Control, InnerQuiet);

	float GS_Bonus;//Bonus from Great Strides
	if (GreatStrides > 0) {
		GS_Bonus = 1;
	}
	else {
		GS_Bonus = 0;
	}
	float I_Bonus;
	if (Innovation > 0) {
		I_Bonus = 0.5;
	}
	else {
		I_Bonus = 0;
	}

	float C_Bonus;//tells us the bonus from condition
	if (Good) {
		C_Bonus = 1.5;
	}
	else if (Excellent) {
		C_Bonus = 4;
	}
	else {
		C_Bonus = 1;
	}

	int integer = int((C_Bonus) * (1 + GS_Bonus + I_Bonus) * Quality);
	return integer;
}

int RapidSynthesis(int Craftsmanship, int Veneration, int MuscleMemory) {
	float Progress = ProgressEquation(Craftsmanship);

	float V_Bonus;//tells us the bonus to include for Veneration
	if (Veneration > 0) {
		V_Bonus = 0.5;
	}
	else {
		V_Bonus = 0;
	}
	float M_Bonus;//tells us the bonus to include for Veneration
	if (MuscleMemory > 0) {
		M_Bonus = 1;
	}
	else {
		M_Bonus = 0;
	}

	int integer = int((1 + V_Bonus + M_Bonus) * (2.5 * Progress));
	return integer;
}

int RapidSynthesisMastered(int Craftsmanship, int Veneration, int MuscleMemory) {
	float Progress = ProgressEquation(Craftsmanship);

	float  V_Bonus;//tells us the bonus to include for Veneration
	if (Veneration > 0) {
		V_Bonus = 0.5;
	}
	else {
		V_Bonus = 0;
	}

	float M_Bonus;//tells us the bonus to include for Veneration
	if (MuscleMemory > 0) {
		M_Bonus = 1;
	}
	else {
		M_Bonus = 0;
	}

	int integer = int((1 + V_Bonus + M_Bonus) * (5 * Progress));
	return integer;

}

//Inner Quiet will be done in the loop since it's more a conditional thing

//Observe will be the same

//Tricks of the Trade, same

//Waste Not

//Veneration

int StandardTouch(int Control, int InnerQuiet, int GreatStrides, int Innovation, bool Good, bool Excellent) {
	float Quality = QualityEquation(Control, InnerQuiet);

	float GS_Bonus;//Bonus from Great Strides
	if (GreatStrides > 0) {
		GS_Bonus = 1;
	}
	else {
		GS_Bonus = 0;
	}
	float I_Bonus;
	if (Innovation > 0) {
		I_Bonus = 0.5;
	}
	else {
		I_Bonus = 0;
	}

	float C_Bonus;//tells us the bonus from condition
	if (Good) {
		C_Bonus = 1.5;
	}
	else if (Excellent) {
		C_Bonus = 4;
	}
	else {
		C_Bonus = 1;
	}

	int integer = int((C_Bonus) * (1 + GS_Bonus + I_Bonus) * (1.25*Quality));
	return integer;
}

//Great Strides

//Innovation

//Name of the Elements

int BrandOfTheElements(int Craftsmanship, int Current_Progress, int NameofTheElements) {//Find out about bonus
	float Progress = ProgressEquation(Craftsmanship);

	//Figure stuff out with Name of the Elements

	int integer;
	if (NameofTheElements > 0) {
		integer= int((1 + 0) * Progress);
	}
	else {
		integer = int(Progress);
	}
	return integer;

}

//Final Appraisal

//Waste Not II

int ByregotsBlessing(int Control, int InnerQuiet, bool Good, bool Excellent) {//Make sure that this only occurs when Inner quiet is 1 or more.
	float Quality = QualityEquation(Control, InnerQuiet);

	float Multiply = 0.20 * (float(InnerQuiet) - 1);

	float C_Bonus;//tells us the bonus from condition
	if (Good) {
		C_Bonus = 1.5;
	}
	else if (Excellent) {
		C_Bonus = 4;
	}
	else {
		C_Bonus = 1;
	}

	int integer = int((C_Bonus) * ((1+Multiply) * Quality));
	return integer;
}

int PreciseTouch(int Control, int InnerQuiet, int GreatStrides, int Innovation, bool Good, bool Excellent) {
	float Quality = QualityEquation(Control, InnerQuiet);

	float GS_Bonus;//Bonus from Great Strides
	if (GreatStrides > 0) {
		GS_Bonus = 1;
	}
	else {
		GS_Bonus = 0;
	}
	float I_Bonus;
	if (Innovation > 0) {
		I_Bonus = 0.5;
	}
	else {
		I_Bonus = 0;
	}

	float C_Bonus;//tells us the bonus from condition
	if (Good) {
		C_Bonus = 1.5;
	}
	else if (Excellent) {
		C_Bonus = 4;
	}
	else {
		C_Bonus = 1;
	}

	int integer = int((C_Bonus) * (1 + GS_Bonus + I_Bonus) * (1.5 * Quality));
	return integer;
}

int MuscleMemory(int Craftsmanship) {//Find out about bonus
	float Progress = ProgressEquation(Craftsmanship);

	

	int integer = int(3 * Progress);
	return integer;
}

int CarefulSynthesis(int Craftsmanship, int Veneration, int MuscleMemory) {
	float Progress = ProgressEquation(Craftsmanship);

	float  V_Bonus;//tells us the bonus to include for Veneration
	if (Veneration > 0) {
		V_Bonus = 0.5;
	}
	else {
		V_Bonus = 0;
	}

	float M_Bonus;//tells us the bonus to include for Veneration
	if (MuscleMemory > 0) {
		M_Bonus = 1;
	}
	else {
		M_Bonus = 0;
	}

	int integer = int((1 + V_Bonus + M_Bonus) * (1.5 * Progress));
	return integer;

}

int PatientTouch(int Control, int InnerQuiet, int GreatStrides, int Innovation, bool Good, bool Excellent) {//Going to pretty much treat it like Basic Touch and find the average between the two between pass and fail, since this also involves status stuff
	float Quality = QualityEquation(Control, InnerQuiet);

	float GS_Bonus;//Bonus from Great Strides
	if (GreatStrides > 0) {
		GS_Bonus = 1;
	}
	else {
		GS_Bonus = 0;
	}
	float I_Bonus;
	if (Innovation > 0) {
		I_Bonus = 0.5;
	}
	else {
		I_Bonus = 0;
	}

	float C_Bonus;//tells us the bonus from condition
	if (Good) {
		C_Bonus = 1.5;
	}
	else if (Excellent) {
		C_Bonus = 4;
	}
	else {
		C_Bonus = 1;
	}

	int integer = int((C_Bonus) * (1 + GS_Bonus + I_Bonus) * Quality);
	return integer;
}

int PrudentTouch(int Control, int InnerQuiet, int GreatStrides, int Innovation, bool Good, bool Excellent) {//Very similar to Basic Touch, I just need to include durability cost stuff later
	float Quality = QualityEquation(Control, InnerQuiet);

	float GS_Bonus;//Bonus from Great Strides
	if (GreatStrides > 0) {
		GS_Bonus = 1;
	}
	else {
		GS_Bonus = 0;
	}
	float I_Bonus;
	if (Innovation > 0) {
		I_Bonus = 0.5;
	}
	else {
		I_Bonus = 0;
	}

	float C_Bonus;//tells us the bonus from condition
	if (Good) {
		C_Bonus = 1.5;
	}
	else if (Excellent) {
		C_Bonus = 4;
	}
	else {
		C_Bonus = 1;
	}

	int integer = int((C_Bonus) * (1 + GS_Bonus + I_Bonus) * Quality);
	return integer;
}

int FocusedSynthesis(int Craftsmanship, int Veneration, int MuscleMemory) {//In case of success
	float Progress = ProgressEquation(Craftsmanship);

	float  V_Bonus;//tells us the bonus to include for Veneration
	if (Veneration > 0) {
		V_Bonus = 0.5;
	}
	else {
		V_Bonus = 0;
	}

	float M_Bonus;//tells us the bonus to include for Veneration
	if (MuscleMemory > 0) {
		M_Bonus = 1;
	}
	else {
		M_Bonus = 0;
	}


	int integer = int((1 + V_Bonus + M_Bonus) * (2 * Progress));
	return integer;

}

int FocusedTouch(int Control, int InnerQuiet, int GreatStrides, int Innovation, bool Good, bool Excellent) {//in case of success
	float Quality = QualityEquation(Control, InnerQuiet);

	float GS_Bonus;//Bonus from Great Strides
	if (GreatStrides > 0) {
		GS_Bonus = 1;
	}
	else {
		GS_Bonus = 0;
	}
	float I_Bonus;
	if (Innovation > 0) {
		I_Bonus = 0.5;
	}
	else {
		I_Bonus = 0;
	}

	float C_Bonus;//tells us the bonus from condition
	if (Good) {
		C_Bonus = 1.5;
	}
	else if (Excellent) {
		C_Bonus = 4;
	}
	else {
		C_Bonus = 1;
	}



	int integer = int((C_Bonus) * (1 + GS_Bonus + I_Bonus) * (1.5 * Quality));
	return integer;
}

int Reflect(int Control, int InnerQuiet){//Going to include Inner Quiet Stuff outside of htis
	float Quality = QualityEquation(Control, InnerQuiet);

	int integer = int(Quality);
	return integer;
}

int PrepatoryTouch(int Control, int InnerQuiet, int GreatStrides, int Innovation, bool Good, bool Excellent) {//Note the inner quiet bonus and durability penalty
	float Quality = QualityEquation(Control, InnerQuiet);

	float GS_Bonus;//Bonus from Great Strides
	if (GreatStrides > 0) {
		GS_Bonus = 1;
	}
	else {
		GS_Bonus = 0;
	}
	float I_Bonus;
	if (Innovation > 0) {
		I_Bonus = 0.5;
	}
	else {
		I_Bonus = 0;
	}

	float C_Bonus;//tells us the bonus from condition
	if (Good) {
		C_Bonus = 1.5;
	}
	else if (Excellent) {
		C_Bonus = 4;
	}
	else {
		C_Bonus = 1;
	}

	int integer = int((C_Bonus) * (1 + GS_Bonus + I_Bonus) * (1.25 * Quality));
	return integer;
}

int Groundwork(int Craftsmanship, bool EnoughDur) {
	float Progress = ProgressEquation(Craftsmanship);

	float Penalty;
	if (EnoughDur) {
		Penalty = 3;
	}
	else {
		Penalty = 1.5;
	}

	int integer = int(Penalty * Progress);
	return integer;
}

int DelicateSynthesisProgress(int Craftsmanship, int Veneration, int MuscleMemory) {
	float Progress = ProgressEquation(Craftsmanship);

	float  V_Bonus;//tells us the bonus to include for Veneration
	if (Veneration > 0) {
		V_Bonus = 0.5;
	}
	else {
		V_Bonus = 0;
	}

	float M_Bonus;//tells us the bonus to include for Veneration
	if (MuscleMemory > 0) {
		M_Bonus = 1;
	}
	else {
		M_Bonus = 0;
	}

	int integer = int((1 + V_Bonus + M_Bonus) * (Progress));
	return integer;

}

int DelicateSynthesisQuality(int Control, int InnerQuiet, int Veneration, int MuscleMemory, bool Good, bool Excellent) {//Very similar to Basic Touch, I just need to include durability cost stuff later
	float Quality = QualityEquation(Control, InnerQuiet);

	float  V_Bonus;//tells us the bonus to include for Veneration
	if (Veneration > 0) {
		V_Bonus = 0.5;
	}
	else {
		V_Bonus = 0;
	}

	float M_Bonus;//tells us the bonus to include for Veneration
	if (MuscleMemory > 0) {
		M_Bonus = 1;
	}
	else {
		M_Bonus = 0;
	}

	float C_Bonus;//tells us the bonus from condition
	if (Good) {
		C_Bonus = 1.5;
	}
	else if (Excellent) {
		C_Bonus = 4;
	}
	else {
		C_Bonus = 1;
	}

	int integer = int((C_Bonus) * (1 + V_Bonus + M_Bonus) * Quality);
	return integer;
}

int IntensiveSyntehsis(int Craftsmanship, int Veneration, int MuscleMemory) {
	float Progress = ProgressEquation(Craftsmanship);

	float  V_Bonus;//tells us the bonus to include for Veneration
	if (Veneration > 0) {
		V_Bonus = 0.5;
	}
	else {
		V_Bonus = 0;
	}

	float M_Bonus;//tells us the bonus to include for Veneration
	if (MuscleMemory > 0) {
		M_Bonus = 1;
	}
	else {
		M_Bonus = 0;
	}

	int integer = int((1 + V_Bonus + M_Bonus) * (3 * Progress));
	return integer;
}

//Trained Eye looks special. Going to set it seperate. 