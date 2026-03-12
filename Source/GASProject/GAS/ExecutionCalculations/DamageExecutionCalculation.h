// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "DamageExecutionCalculation.generated.h"


class UHealthSet;

struct FDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArmorHealth);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArmorAbsorption);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Health);
	DECLARE_ATTRIBUTE_CAPTUREDEF(IncomingDamage);
	
	FDamageStatics();
};

UCLASS()
class GASPROJECT_API UDamageExecutionCalculation : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
	
public:
	static const FDamageStatics& DamageStatics();
	
	UDamageExecutionCalculation();
	
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
