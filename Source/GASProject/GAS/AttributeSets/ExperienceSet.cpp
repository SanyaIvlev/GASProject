// Fill out your copyright notice in the Description page of Project Settings.


#include "ExperienceSet.h"

#include "GameplayEffectExtension.h"

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

void UExperienceSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	
	if (Data.EvaluatedData.Attribute == GetExperienceAttribute())
	{
		float NewExperience = GetExperience();
		
		if (NewExperience >= GetNeededExperience())
		{
			SetLevel(GetLevel() + 1);
			SetExperience(GetNeededExperience() - NewExperience);
			
			CalculateNeededExperience();
		}
	}
	else if (Data.EvaluatedData.Attribute == GetLevelAttribute())
	{
		CalculateNeededExperience();
	}
	
	OnAttributesUpdated.Broadcast();
}

