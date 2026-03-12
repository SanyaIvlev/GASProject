// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputTagsSettings.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "InputTagSubsystem.generated.h"

UCLASS()
class GASPROJECT_API UInputTagSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	UInputAction* GetInputAction(FGameplayTag Tag);
	static UInputTagSubsystem* GetInputTagSubsystem(const UWorld* WorldContextObject);
	
private:
	UPROPERTY()
	TMap<FGameplayTag, TSoftObjectPtr<UInputAction>> InputActionInfos;
};
