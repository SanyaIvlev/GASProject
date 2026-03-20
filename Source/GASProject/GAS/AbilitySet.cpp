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
	
	FGivenAbilitiesHandle& CharacterAbilitiesHandle = GivenHandles.Add(AbilityCharacter);
	
	for (auto& AbilityInfo : Abilities)
	{
		UGameplayAbility* AbilityToGrant = AbilityInfo.Ability->GetDefaultObject<UGameplayAbility>();
		 
		FGameplayAbilitySpec AbilitySpec(AbilityToGrant);
		AbilitySpec.SourceObject = AbilityCharacter;
		FGameplayTag Tag = AbilityInfo.InputTag;
		
		if (!Tag.IsValid())
		{
			ASC->GiveAbility(AbilitySpec);
			continue;
		}
		
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

	for (auto Effect : Effects)
	{
		UGameplayEffect* EffectDefaultObject = Effect->GetDefaultObject<UGameplayEffect>();
		
		FActiveGameplayEffectHandle EffectHandle = ASC->ApplyGameplayEffectToSelf(EffectDefaultObject, 1, FGameplayEffectContextHandle());
		CharacterAbilitiesHandle.ActiveGameplayEffectHandles.Add(EffectHandle);
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
	
	FGivenAbilitiesHandle* CharacterAbilities = GivenHandles.Find(AbilityCharacter);
	
	if (CharacterAbilities == nullptr)
	{
		return;
	}
	
	for (auto& AbilitySpec : CharacterAbilities->AbilitySpecs)
	{
		ASC->ClearAbility(AbilitySpec.Handle);
	}
	
	for (auto ActiveEffectHandle : CharacterAbilities->ActiveGameplayEffectHandles)
	{
		ASC->RemoveActiveGameplayEffect(ActiveEffectHandle);
	}
	
	GivenHandles.Remove(AbilityCharacter);
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
	
	FGivenAbilitiesHandle* ActorAbilitiesHandle = GivenHandles.Find(DestroyedCharacter);
	
	if (ActorAbilitiesHandle == nullptr)
	{
		return;
	}
	
	for (int32 Binding : ActorAbilitiesHandle->InputBindings)
	{
		EIC->RemoveBindingByHandle(Binding);
	}
}
