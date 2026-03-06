#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PickUpInfo.generated.h"


class UGameplayEffect;

UCLASS()
class GASPROJECT_API UPickUpInfo : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UGameplayEffect* PickUpEffect;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText PickUpText;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bHasDuration;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "bHasDuration"))
	float Duration;
};
