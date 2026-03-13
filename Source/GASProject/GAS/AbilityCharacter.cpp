#include "AbilityCharacter.h"

#include "AbilitySet.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "CharacterAttributesData.h"

void AAbilityCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	check(AbilitySystemComponent);
	
	AbilitySystemComponent->RegisterGenericGameplayTagEvent().AddUObject(this, &AAbilityCharacter::OnGameplayTagUpdated);
}

void AAbilityCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
		
	if (StartingAbilitySet != nullptr)
	{
		StartingAbilitySet->GiveAbilities(this);
	}
}

UAbilitySystemComponent* AAbilityCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

float AAbilityCharacter::GetCooldownRemaining(FGameplayTag CooldownTag) const
{
	if (IsValid(AbilitySystemComponent))
	{
		FGameplayEffectQuery const Query = FGameplayEffectQuery::MakeQuery_MatchAnyOwningTags(FGameplayTagContainer(CooldownTag));
        
		TArray<float> TimesRemaining = AbilitySystemComponent->GetActiveEffectsTimeRemaining(Query);
        
		if (TimesRemaining.Num() > 0)
		{
			float MaxTime = TimesRemaining[0];
			
			for (float Time : TimesRemaining)
			{
				if (Time > MaxTime) MaxTime = Time;
			}
			return MaxTime;
		}
	}
	return 0.f;
}

void AAbilityCharacter::InitializeAttributeSetsFromData(UCharacterAttributesData* AttributeSetData)
{
	check(AbilitySystemComponent);
	
	for (auto& AttributeSet : AttributeSetData->AttributeSets)
	{
		UClass* SetClass = AttributeSet.LoadSynchronous();
		
		if (SetClass == nullptr)
		{
			continue;
		}
		
		UAttributeSet* NewAttributeSet = NewObject<UAttributeSet>(this, SetClass);
        
		AbilitySystemComponent->AddAttributeSetSubobject(NewAttributeSet);
	}
}

void AAbilityCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	
	AbilitySystemComponent->RegisterGenericGameplayTagEvent().RemoveAll(this);
}

void AAbilityCharacter::OnGameplayTagUpdated(const FGameplayTag Tag, int32 TagCount) const
{
	OnAnyTagChanged.Broadcast(Tag, TagCount > 0);
}

