// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DeveloperSettings.h"
#include "DebugCommandsConfiguration.generated.h"

class UGameplayEffect;

UCLASS(Config=Game, defaultconfig, meta=(DisplayName="Debug Command Configuration"))
class GASPROJECT_API UDebugCommandsConfiguration : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Healing Command")
	TSoftClassPtr<UGameplayEffect> HealingEffect;
	
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Damaging Command")
	TSoftClassPtr<UGameplayEffect> DamagingEffect;
	
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Damaging Command")
	float DamageMagnitude;
	
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Damaging Command")
	FGameplayTag DamageSetByCallerTag;
	
	static const UDebugCommandsConfiguration* GetConfig();
};
