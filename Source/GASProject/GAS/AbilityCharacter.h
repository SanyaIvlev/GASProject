#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Character.h"
#include "AbilityCharacter.generated.h"

class UAbilitySet;
class UCharacterAttributesData;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAnyTagChanged, FGameplayTag, Tag, bool, bIsPresent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDeath, AAbilityCharacter*, Character);

UCLASS()
class GASPROJECT_API AAbilityCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAbilitySet* StartingAbilitySet;
	
	UPROPERTY(BlueprintAssignable)
	FOnAnyTagChanged OnAnyTagChanged;
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnDeath OnDeath;
	
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	UFUNCTION(BlueprintCallable)
	float GetCooldownRemaining(FGameplayTag Tag) const;
	
	UFUNCTION(BlueprintCallable)
	void InitializeAttributeSetsFromData(UCharacterAttributesData* AttributeSetData);
	
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAbilitySystemComponent* AbilitySystemComponent;
	
	void OnGameplayTagUpdated(const FGameplayTag Tag, int32 TagCount) const;
};
