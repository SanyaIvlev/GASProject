#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "DamageSet.generated.h"

UCLASS()
class GASPROJECT_API UDamageSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UDamageSet();
	
	ATTRIBUTE_ACCESSORS_BASIC(UDamageSet, BaseDamage);
	
	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData BaseDamage;
	
protected:
	UFUNCTION(BlueprintCallable)
	void InitializeBaseDamage(float NewValue);
};
