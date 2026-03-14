// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbilitySpec.h"
#include "Engine/DataAsset.h"
#include "AbilitySet.generated.h"


class AAbilityCharacter;
class UAbilitySystemComponent;

USTRUCT()
struct FAbilityInfo
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayAbility> Ability;
	
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag;
};

USTRUCT()
struct FCharacterGivenAbilitiesHandle
{
	GENERATED_BODY()
	
public:
	TArray<FGameplayAbilitySpec> AbilitySpecs;
	
	TArray<int32> InputBindings;
};


UCLASS()
class GASPROJECT_API UAbilitySet : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly)
	TArray<FAbilityInfo> Abilities;
	
	void GiveAbilities(AAbilityCharacter* AbilityCharacter);
	void RemoveAbilities(AAbilityCharacter* AbilityCharacter);
	
private:
	TMap<AActor*, FCharacterGivenAbilitiesHandle> GivenAbilities;
	
	UFUNCTION()
	void OnCharacterDestroyed(AAbilityCharacter* DestroyedCharacter);
	void RemoveBindings(AAbilityCharacter* DestroyedCharacter);
};
