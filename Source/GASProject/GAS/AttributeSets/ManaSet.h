#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "ManaSet.generated.h"


UCLASS()
class GASPROJECT_API UManaSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UManaSet();
	
	ATTRIBUTE_ACCESSORS_BASIC(UManaSet, Mana);
	ATTRIBUTE_ACCESSORS_BASIC(UManaSet, MaxMana);
	
	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData Mana;
	
	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData MaxMana;
	
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
	
protected:
	float MinMana;
};
