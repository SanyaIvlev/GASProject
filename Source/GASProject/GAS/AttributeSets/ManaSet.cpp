// Fill out your copyright notice in the Description page of Project Settings.


#include "ManaSet.h"

#include "GameplayEffectExtension.h"

UManaSet::UManaSet() : Mana(100), MaxMana(100.0f) 
{
	MinMana = 0;
}

void UManaSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(), MinMana, GetMaxMana()));
	}
}
