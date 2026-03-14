// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "ExperienceSet.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUpdatedAttributes);

UCLASS()
class GASPROJECT_API UExperienceSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	ATTRIBUTE_ACCESSORS_BASIC(UExperienceSet, Level)
	ATTRIBUTE_ACCESSORS_BASIC(UExperienceSet, Experience)
	
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UExperienceSet, NeededExperience)
	GAMEPLAYATTRIBUTE_VALUE_GETTER(NeededExperience) 
	GAMEPLAYATTRIBUTE_VALUE_INITTER(NeededExperience)
	
	UPROPERTY(BlueprintAssignable)
	FOnUpdatedAttributes OnAttributesUpdated;
	
	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData Level;
	
	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData Experience;
	
	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData NeededExperience;
	
	UExperienceSet();
	
	void CalculateNeededExperience();
	
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
	
protected:
	GAMEPLAYATTRIBUTE_VALUE_SETTER(NeededExperience)
	
	float StartingLevel;
};
