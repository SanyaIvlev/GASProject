// Fill out your copyright notice in the Description page of Project Settings.


#include "RuntimeDebugCommands.h"

#include "AbilitySystemComponent.h"
#include "DebugCommandsConfiguration.h"
#include "GASProject/GAS/AbilityCharacter.h"
#include "Kismet/GameplayStatics.h"

void URuntimeDebugCommands::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
	AbilityCharacter = Cast<AAbilityCharacter>(PlayerCharacter);
	
	Configuration = UDebugCommandsConfiguration::GetConfig();
	
	TSubclassOf<UGameplayEffect> LoadedHealEffect = Configuration->HealingEffect.LoadSynchronous();
	HealEffect = LoadedHealEffect->GetDefaultObject<UGameplayEffect>();
	
	LoadedDamagingEffect = Configuration->DamagingEffect.LoadSynchronous();
	
	
	IConsoleObject* HealCommand = IConsoleManager::Get().RegisterConsoleCommand(
	TEXT("Character.Heal"),
	TEXT("Heals player character next 5 seconds"),
	FConsoleCommandWithWorldAndArgsDelegate::CreateUObject(this, &URuntimeDebugCommands::HealCharacter),
	ECVF_Cheat
	);
	
	RegisteredCommands.Add(HealCommand);
	
	IConsoleObject* DamageCommand = IConsoleManager::Get().RegisterConsoleCommand(
	TEXT("Character.DealDamage"),
	TEXT("Deals damage set in the settings to the player character"),
	FConsoleCommandWithWorldAndArgsDelegate::CreateUObject(this, &URuntimeDebugCommands::DamageCharacter),
	ECVF_Cheat
	);
	
	RegisteredCommands.Add(DamageCommand);
}

void URuntimeDebugCommands::Deinitialize()
{
	Super::Deinitialize();
	
	for (auto& Command : RegisteredCommands)
	{
		IConsoleManager::Get().UnregisterConsoleObject(Command);
	}
	
	RegisteredCommands.Empty();
}

void URuntimeDebugCommands::HealCharacter(const TArray<FString>& Args, UWorld* World)
{
	if (!AbilityCharacter)
	{
		ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
		AbilityCharacter = Cast<AAbilityCharacter>(PlayerCharacter);
	}
	
	if (!AbilitySystemComponent)
	{
		AbilitySystemComponent = AbilityCharacter->GetAbilitySystemComponent();
	}
	
	AbilitySystemComponent->ApplyGameplayEffectToSelf(HealEffect, 0, FGameplayEffectContextHandle());
}

void URuntimeDebugCommands::DamageCharacter(const TArray<FString>& Args, UWorld* World)
{
	if (!AbilityCharacter)
	{
		ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
		AbilityCharacter = Cast<AAbilityCharacter>(PlayerCharacter);
	}
	
	if (!AbilitySystemComponent)
	{
		AbilitySystemComponent = AbilityCharacter->GetAbilitySystemComponent();
	}
	
	FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(LoadedDamagingEffect, 0, AbilitySystemComponent->MakeEffectContext());
	
	SpecHandle.Data.Get()->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(Configuration->DamageSetByCallerTag.GetTagName()), Configuration->DamageMagnitude);
	
	AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
}
