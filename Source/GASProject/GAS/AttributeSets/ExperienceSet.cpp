// Fill out your copyright notice in the Description page of Project Settings.


#include "ExperienceSet.h"

UExperienceSet::UExperienceSet() : Level(0), Experience(0), NeededExperience(1.5f * 1 * 1 - 1.5f * 1 + 1)
{
	StartingLevel = 0;
}

void UExperienceSet::CalculateNeededExperience()
{
	float NextLevel = GetLevel();
	SetNeededExperience(1.5f * NextLevel * NextLevel - 1.5f * NextLevel + 1);
}

void UExperienceSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	
	if (Attribute == GetLevelAttribute() && NewValue < StartingLevel)
	{
		NewValue = StartingLevel;
	}
}

void UExperienceSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);
	
	if (Attribute == GetExperienceAttribute())
	{
		if (NewValue >= GetNeededExperience())
		{
			SetLevel(GetLevel() + 1);
			SetExperience(GetNeededExperience() - NewValue);
			
			CalculateNeededExperience();
		}
	}
	else if (Attribute == GetLevelAttribute())
	{
		CalculateNeededExperience();
	}
}
