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
	
	if (StartingAbilitySet != nullptr)
	{
		StartingAbilitySet->GiveAbilities(AbilitySystemComponent, this);
	}
}

UAbilitySystemComponent* AAbilityCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
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

