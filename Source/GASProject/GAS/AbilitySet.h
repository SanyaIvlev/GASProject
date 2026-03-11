// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilityInfo.h"
#include "Engine/DataAsset.h"
#include "AbilitySet.generated.h"


class UAbilitySystemComponent;

UCLASS()
class GASPROJECT_API UAbilitySet : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	
	TArray<FAbilityInfo> Abilities;
	
	void GiveAbilities(UAbilitySystemComponent* AbilitySystemComponent, UObject* SourceObject) const;
};
