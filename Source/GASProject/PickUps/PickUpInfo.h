#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "PickUpInfo.generated.h"

class UGameplayEffect;

UCLASS()
class GASPROJECT_API UPickUpInfo : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> PickUpEffect;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText PickUpText;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bHasDuration;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "bHasDuration"))
	float Duration;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bDoesUseEffectSpec;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "bDoesUseEffectSpec"))
	FGameplayTag SpecDataTag;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "bDoesUseEffectSpec"))
	float SpecMagnitude;
	
};
