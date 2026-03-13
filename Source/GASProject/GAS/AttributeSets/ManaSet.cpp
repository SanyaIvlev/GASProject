// Fill out your copyright notice in the Description page of Project Settings.


#include "ManaSet.h"

UManaSet::UManaSet() : Mana(100), MaxMana(100.0f) 
{
	MinMana = 0;
}

void UManaSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	
	if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, MinMana, GetMaxMana());
	}
}
