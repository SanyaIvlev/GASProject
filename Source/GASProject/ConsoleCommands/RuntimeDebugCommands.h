// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "HAL/IConsoleManager.h"
#include "RuntimeDebugCommands.generated.h"


class UGameplayEffect;
class UDebugCommandsConfiguration;
class UAbilitySystemComponent;
class AAbilityCharacter;

UCLASS()
class GASPROJECT_API URuntimeDebugCommands : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	virtual void Deinitialize() override;
	
	void HealCharacter(const TArray<FString>& Args, UWorld* World);
	void DamageCharacter(const TArray<FString>& Args, UWorld* World);
	
private:
	UPROPERTY()
	AAbilityCharacter* AbilityCharacter;
	
	UPROPERTY()
	UAbilitySystemComponent* AbilitySystemComponent;
	
	UPROPERTY()
	const UDebugCommandsConfiguration* Configuration;
	
	UPROPERTY()
	UGameplayEffect* HealEffect;
	
	UPROPERTY()
	TSubclassOf<UGameplayEffect> LoadedDamagingEffect;
	
	TArray<IConsoleObject*> RegisteredCommands;
};
