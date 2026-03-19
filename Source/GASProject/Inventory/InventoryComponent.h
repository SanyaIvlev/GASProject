#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "ItemBase.h"
#include "InventoryComponent.generated.h"

USTRUCT(BlueprintType)
struct FInventorySlot
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	AItemBase* Item;

	FInventorySlot() : Item(nullptr) {}

	bool IsEmpty() const { return !IsValid(Item); }
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdated);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemActivated, bool, bIsActivated);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GASPROJECT_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventoryComponent();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	int32 MaxSlots = 3;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	TArray<FInventorySlot> Slots;

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnInventoryUpdated OnInventoryUpdated;
	
	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnItemActivated OnItemActivated;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool AddItem(AItemBase* NewItem);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool RemoveItemByTag(FGameplayTag ItemTag);
	
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	UInventoryItemData* GetItemData(int32 Index);
	
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void ActivateItem(const FGameplayTag Tag, bool bIsActivated);

	UFUNCTION(BlueprintPure, Category = "Inventory")
	const TArray<FInventorySlot>& GetSlots() const { return Slots; }
};
