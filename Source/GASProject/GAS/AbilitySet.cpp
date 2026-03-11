// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySet.h"

#include "AbilitySystemComponent.h"
#include "Abilities/GameplayAbility.h"

void UAbilitySet::GiveAbilities(UAbilitySystemComponent* AbilitySystemComponent, UObject* SourceObject) const
{
	if (AbilitySystemComponent == nullptr)
	{
		return;
	}
	
	for (auto& AbilityInfo : Abilities)
	{
		UGameplayAbility* AbilityToGrant = AbilityInfo.Ability->GetDefaultObject<UGameplayAbility>();
		
		FGameplayAbilitySpec AbilitySpec(AbilityToGrant);
		AbilitySpec.SourceObject = SourceObject;
		
		AbilitySpec.GetDynamicSpecSourceTags().AddTag(AbilityInfo.InputTag);
		
		AbilitySystemComponent->GiveAbility(AbilitySpec);
	}
}
