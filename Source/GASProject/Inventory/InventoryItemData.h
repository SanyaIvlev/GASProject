 #pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "InventoryItemData.generated.h"

class UAbilitySet;

UCLASS(BlueprintType)
class GASPROJECT_API UInventoryItemData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	FGameplayTag ItemTag;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	FText ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	TSubclassOf<UAnimInstance> ActivationAnimInstance;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	UAbilitySet* AbilitySet;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	UTexture2D* Icon;

	// Add more info as needed, like weapon class, etc.
};
