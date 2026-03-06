	#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "DamageSet.generated.h"


#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class GASPROJECT_API UDamageSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UDamageSet();
	
	ATTRIBUTE_ACCESSORS(UDamageSet, BaseDamage);
	
protected:
	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData BaseDamage;
};
