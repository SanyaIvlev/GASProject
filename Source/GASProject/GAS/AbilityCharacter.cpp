#include "AbilityCharacter.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "CharacterAttributesData.h"

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

