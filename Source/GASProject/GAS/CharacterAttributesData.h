#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CharacterAttributesData.generated.h"

class UAttributeSet;

UCLASS()
class GASPROJECT_API UCharacterAttributesData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<TSoftClassPtr<UAttributeSet>> AttributeSets;
};
