#pragma once

int FindLevelMod(int CLVL, int RLVL);
float BaseProgress(int Craftsmanship, int RLVL, int LevelMod, int stars);
float IQ(int Control, int IQStacks);
float BaseQuality(int Control, int IQStacks, int RLVL, int LevelMod, int stars);
float Condition(bool Poor, bool Good, bool Excellent);
float EfficencyEquation(float Efficiency, int Veneration_Innovation, int GreatStrides_MuscleMemory);
float ByregotsBlessing(int IQStacks);
float NameOfTheElements(int currentProgress, int totalProgress);