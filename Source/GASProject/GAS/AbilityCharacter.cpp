#include "AbilityCharacter.h"

#include "HealthSet.h"

AAbilityCharacter::AAbilityCharacter()
{
	CreateDefaultSubobject<UHealthSet>(TEXT("HealthSet"));
}

UAbilitySystemComponent* AAbilityCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

