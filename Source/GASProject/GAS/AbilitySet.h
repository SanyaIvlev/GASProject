// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilityInfo.h"
#include "Engine/DataAsset.h"
#include "AbilitySet.generated.h"


class AAbilityCharacter;
class UAbilitySystemComponent;

UCLASS()
class GASPROJECT_API UAbilitySet : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly)
	TArray<FAbilityInfo> Abilities;
	
	void GiveAbilities(AAbilityCharacter* AbilityCharacter) const;
};
