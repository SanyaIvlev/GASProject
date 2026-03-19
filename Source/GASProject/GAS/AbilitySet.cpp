#include "AbilitySet.h"
#include "AbilityCharacter.h"
#include "AbilitySystemComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputTagSubsystem.h"
#include "InputActionValue.h"
#include "Abilities/GameplayAbility.h"

void UAbilitySet::GiveAbilities(AAbilityCharacter* AbilityCharacter)
{
	UAbilitySystemComponent* ASC = AbilityCharacter->GetAbilitySystemComponent();
	
	if (ASC == nullptr)
	{
		return; 
	}
	
	FCharacterGivenAbilitiesHandle& CharacterAbilitiesHandle = GivenAbilities.Add(AbilityCharacter);
	
	for (auto& AbilityInfo : Abilities)
	{
		UGameplayAbility* AbilityToGrant = AbilityInfo.Ability->GetDefaultObject<UGameplayAbility>();
		 
		FGameplayAbilitySpec AbilitySpec(AbilityToGrant);
		AbilitySpec.SourceObject = AbilityCharacter;
		FGameplayTag Tag = AbilityInfo.InputTag;
		
		AbilitySpec.GetDynamicSpecSourceTags().AddTag(Tag);
		
		UInputComponent* InputComponent = AbilityCharacter->InputComponent;
		UEnhancedInputComponent* EIC = CastChecked<UEnhancedInputComponent>(InputComponent);
		
		UWorld* WorldContext = AbilityCharacter->GetWorld();
		UInputTagSubsystem* InputTagSubsystem = UInputTagSubsystem::GetInputTagSubsystem(WorldContext);
		UInputAction* AbilityInputAction = InputTagSubsystem->GetInputAction(Tag);
		
		FEnhancedInputActionEventBinding& Binding = EIC->BindActionValueLambda(AbilityInputAction, ETriggerEvent::Started, [ASC, Tag](const FInputActionValue& Value)
		{
			if (ASC)
			{
				FGameplayEventData EventData;
				EventData.EventTag = Tag;
				EventData.Instigator = ASC->GetAvatarActor();
		        
				ASC->HandleGameplayEvent(Tag, &EventData);
			}
		});
		
		CharacterAbilitiesHandle.InputBindings.Add(Binding.GetHandle());
		
		CharacterAbilitiesHandle.AbilitySpecs.Add(AbilitySpec);
		
		ASC->GiveAbility(AbilitySpec);
	}
	
	AbilityCharacter->OnDeath.AddDynamic(this, &UAbilitySet::OnCharacterDestroyed);
}

void UAbilitySet::RemoveAbilities(AAbilityCharacter* AbilityCharacter)
{
	RemoveBindings(AbilityCharacter);
	
	UAbilitySystemComponent* ASC = AbilityCharacter->GetAbilitySystemComponent();
	
	if (ASC == nullptr)
	{
		return;
	}
	
	FCharacterGivenAbilitiesHandle* CharacterAbilities = GivenAbilities.Find(AbilityCharacter);
	
	if (CharacterAbilities == nullptr)
	{
		return;
	}
	
	for (auto& AbilitySpec : CharacterAbilities->AbilitySpecs)
	{
		ASC->ClearAbility(AbilitySpec.Handle);
	}
	
	GivenAbilities.Remove(AbilityCharacter);
}

void UAbilitySet::OnCharacterDestroyed(AAbilityCharacter* DestroyedCharacter)
{
	RemoveBindings(DestroyedCharacter);
	DestroyedCharacter->OnDeath.RemoveDynamic(this, &UAbilitySet::OnCharacterDestroyed);
}

void UAbilitySet::RemoveBindings(AAbilityCharacter* DestroyedCharacter)
{
	UInputComponent* InputComponent = DestroyedCharacter->InputComponent;
	UEnhancedInputComponent* EIC = CastChecked<UEnhancedInputComponent>(InputComponent);
	
	FCharacterGivenAbilitiesHandle* ActorAbilitiesHandle = GivenAbilities.Find(DestroyedCharacter);
	
	if (ActorAbilitiesHandle == nullptr)
	{
		return;
	}
	
	for (int32 Binding : ActorAbilitiesHandle->InputBindings)
	{
		EIC->RemoveBindingByHandle(Binding);
	}
}
