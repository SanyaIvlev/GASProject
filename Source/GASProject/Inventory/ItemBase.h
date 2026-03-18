#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InventoryItemData.h"
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

    UFUNCTION(BlueprintPure, Category = "Inventory")
    FGameplayTag GetItemTag() const { return ItemData ? ItemData->ItemTag : FGameplayTag::EmptyTag; }
};
