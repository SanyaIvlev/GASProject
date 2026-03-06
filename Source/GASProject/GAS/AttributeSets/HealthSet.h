#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "HealthSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedDelegate, float, Health);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOutOfHealthDelegate);

UCLASS()
class GASPROJECT_API UHealthSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UHealthSet();
	
	ATTRIBUTE_ACCESSORS(UHealthSet, Health);
	ATTRIBUTE_ACCESSORS(UHealthSet, MaxHealth);
	ATTRIBUTE_ACCESSORS(UHealthSet, IncomingDamage);
	ATTRIBUTE_ACCESSORS(UHealthSet, Healing);
	
	UPROPERTY(BlueprintAssignable)
	FOnHealthChangedDelegate OnHealthChanged;
	
	UPROPERTY(BlueprintAssignable)
	FOnOutOfHealthDelegate OnOutOfHealth;
	
protected:
	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData Health;
	
	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData MaxHealth;
	
	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData Healing;
	
	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData IncomingDamage;
	
	bool bIsOutOfHealth;
	float MinHealth;
	
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
};
