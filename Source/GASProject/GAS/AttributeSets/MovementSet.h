// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "MovementSet.generated.h"

UCLASS()
class GASPROJECT_API UMovementSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	ATTRIBUTE_ACCESSORS_BASIC(UMovementSet, Speed);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData Speed;
	
	UMovementSet();

protected:
	
	float MinSpeed;
	
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
};
