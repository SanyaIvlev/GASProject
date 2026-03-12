// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "EnhancedInputComponent.h"
#include "GameplayTagContainer.h"
#include "InputTagsSettings.generated.h"

UCLASS(Config=Game, DefaultConfig, meta=(DisplayName="Input Tags Settings"))
class GASPROJECT_API UInputTagsSettings : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:
	UPROPERTY(Config, EditDefaultsOnly)
	TMap<FGameplayTag, TSoftObjectPtr<UInputAction>> InputActionTags;
	
	static const UInputTagsSettings* GetConfig();
};
