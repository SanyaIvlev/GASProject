#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InventoryItemData.h"
#include "GASProject/GAS/AbilityCharacter.h"
#include "ItemBase.generated.h"

/**
 * Base class for all inventory items as Actors.
 */
UCLASS()
class GASPROJECT_API AItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AItemBase();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	UInventoryItemData* ItemData;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	AAbilityCharacter* ItemOwner;

    UFUNCTION(BlueprintPure, Category = "Inventory")
    FGameplayTag GetItemTag() const { return ItemData ? ItemData->ItemTag : FGameplayTag::EmptyTag; }
	
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SetItemOwner(AAbilityCharacter* NewOwner);
	
	void ProcessActivation(bool bIsActivated);
};
