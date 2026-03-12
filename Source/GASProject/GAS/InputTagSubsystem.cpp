// Fill out your copyright notice in the Description page of Project Settings.


#include "InputTagSubsystem.h"

#include "InputTagsSettings.h"
#include "Kismet/GameplayStatics.h"

void UInputTagSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	const UInputTagsSettings* Settings =  UInputTagsSettings::GetConfig();
	
	InputActionInfos = Settings->InputActionTags;
}

UInputAction* UInputTagSubsystem::GetInputAction(FGameplayTag Tag)
{
	TSoftObjectPtr<UInputAction>* FoundAction = InputActionInfos.Find(Tag);
	UInputAction* LoadedAction = FoundAction->LoadSynchronous();
	
	return LoadedAction;
}

UInputTagSubsystem* UInputTagSubsystem::GetInputTagSubsystem(const UWorld* WorldContextObject)
{
	return UGameplayStatics::GetGameInstance(WorldContextObject)->GetSubsystem<UInputTagSubsystem>();
}
