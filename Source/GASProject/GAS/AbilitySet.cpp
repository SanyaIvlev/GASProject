#include "AbilitySet.h"
#include "AbilityCharacter.h"
#include "AbilitySystemComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputTagSubsystem.h"
#include "InputActionValue.h"
#include "Abilities/GameplayAbility.h"
#include "Kismet/GameplayStatics.h"

void UAbilitySet::GiveAbilities(AAbilityCharacter* AbilityCharacter) const
{
	UAbilitySystemComponent* ASC = AbilityCharacter->GetAbilitySystemComponent();
	
	if (ASC == nullptr)
	{
		return;
	}
	
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
		
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(WorldContext, 0);
		
		EIC->BindActionValueLambda(AbilityInputAction, ETriggerEvent::Started, [ASC, Tag](const FInputActionValue& Value)
		{
			if (ASC)
			{
				FGameplayEventData EventData;
				EventData.EventTag = Tag;
				EventData.Instigator = ASC->GetAvatarActor();
		        
				ASC->HandleGameplayEvent(Tag, &EventData);
			}
		});
		
		ASC->GiveAbility(AbilitySpec);
	}
}
