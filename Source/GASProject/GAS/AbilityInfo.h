#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Class.h"
#include "AbilityInfo.generated.h"

class UGameplayAbility;

USTRUCT()
struct FAbilityInfo
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayAbility> Ability;
	
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag;
};
