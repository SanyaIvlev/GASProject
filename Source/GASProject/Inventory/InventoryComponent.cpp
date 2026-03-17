#include "InventoryComponent.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// Initialize empty slots
	Slots.SetNum(MaxSlots);
}

bool UInventoryComponent::AddItem(UInventoryItemData* NewItem)
{
	if (!NewItem) return false;

	for (int32 i = 0; i < Slots.Num(); ++i)
	{
		if (Slots[i].IsEmpty())
		{
			Slots[i].ItemData = NewItem;
			OnInventoryUpdated.Broadcast();
			return true;
		}
	}

	return false;
}

bool UInventoryComponent::RemoveItemByTag(FGameplayTag ItemTag)
{
	if (!ItemTag.IsValid()) return false;

	bool bRemoved = false;
	for (int32 i = 0; i < Slots.Num(); ++i)
	{
		if (!Slots[i].IsEmpty() && Slots[i].ItemData->ItemTag.MatchesTag(ItemTag))
		{
			Slots[i].ItemData = nullptr;
			bRemoved = true;
		}
	}

	if (bRemoved)
	{
		OnInventoryUpdated.Broadcast();
	}

	return bRemoved;
}
