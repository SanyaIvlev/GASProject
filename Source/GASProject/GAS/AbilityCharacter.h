// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "AbilityCharacter.generated.h"

UCLASS()
class GASPROJECT_API AAbilityCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAbilitySystemComponent* AbilitySystemComponent;
	
	AAbilityCharacter();

public:
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
};
