#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Character.h"
#include "AbilityCharacter.generated.h"

class UCharacterAttributesData;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAnyTagChanged, FGameplayTag, Tag, bool, bIsPresent);

UCLASS()
class GASPROJECT_API AAbilityCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintAssignable)
	FOnAnyTagChanged OnAnyTagChanged;
	
	virtual void BeginPlay() override;
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	UFUNCTION(BlueprintCallable)
	void InitializeAttributeSetsFromData(UCharacterAttributesData* AttributeSetData);
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAbilitySystemComponent* AbilitySystemComponent;
	
	void OnGameplayTagUpdated(const FGameplayTag Tag, int32 TagCount) const;
};
