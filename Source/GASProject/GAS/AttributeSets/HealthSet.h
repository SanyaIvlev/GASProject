#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "HealthSet.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOutOfHealthDelegate);

UCLASS()
class GASPROJECT_API UHealthSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UHealthSet();
	
	ATTRIBUTE_ACCESSORS_BASIC(UHealthSet, Health);
	ATTRIBUTE_ACCESSORS_BASIC(UHealthSet, MaxHealth);
	ATTRIBUTE_ACCESSORS_BASIC(UHealthSet, ArmorHealth);
	ATTRIBUTE_ACCESSORS_BASIC(UHealthSet, ArmorAbsorption);
	ATTRIBUTE_ACCESSORS_BASIC(UHealthSet, IncomingDamage);
	ATTRIBUTE_ACCESSORS_BASIC(UHealthSet, Healing);
	
	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData Health;
	
	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData MaxHealth;
	
	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData ArmorHealth;
	
	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData ArmorAbsorption;
	
	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData Healing;
	
	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData IncomingDamage;
	
	UPROPERTY(BlueprintAssignable)
	FOnOutOfHealthDelegate OnOutOfHealth;
	
protected:
	bool bIsOutOfHealth;
	float MinHealth;
	
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
};
