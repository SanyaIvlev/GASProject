#include "InventoryComponent.h"

#include "VisualizeTexture.h"

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

bool UInventoryComponent::HasEmptySlots()
{
	for (auto& Slot : Slots)
	{
		if (Slot.IsEmpty())
		{
			return true;
		}
	}
	
	return false;
}

bool UInventoryComponent::AddItem(AItemBase* NewItem)
{
	if (!NewItem)
	{
		return false;
	}

	for (int32 i = 0; i < Slots.Num(); ++i)
	{
		if (Slots[i].IsEmpty())
		{
			Slots[i].Item = NewItem;
			NewItem->ProcessActivation(false); 
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
		if (!Slots[i].IsEmpty() && Slots[i].Item->GetItemTag().MatchesTag(ItemTag))
		{
			Slots[i].Item = nullptr;
			bRemoved = true;
		}
	}

	if (bRemoved)
	{
		OnInventoryUpdated.Broadcast();
	}

	return bRemoved;
}

UInventoryItemData* UInventoryComponent::GetItemData(int32 Index)
{
	FInventorySlot Slot = Slots[Index];
	
	if (Slot.IsEmpty())
	{
		return nullptr;
	}
	
	return Slot.Item->ItemData;
}

void UInventoryComponent::ActivateItem(const FGameplayTag Tag, bool bIsActivated)
{
	AItemBase* Item = nullptr;
	int32 SlotIndex = 0;
	
	for (int i = 0; i < Slots.Num(); ++i)
	{
		auto& Slot = Slots[i];
		
		AItemBase* SlotItem = Slot.Item;
		
		if (Slot.IsEmpty())
		{
			continue;
		}
		
		if (SlotItem->GetItemTag().MatchesTagExact(Tag))
		{
			Item = SlotItem;
			SlotIndex = i;
			break;
		}
	}
	
	if (!IsValid(Item))
	{
		return;
	}
	
	if (bIsActivated)
	{
		ActivatedIndex = SlotIndex;
	}
	
	Item->ProcessActivation(bIsActivated);
	OnItemActivated.Broadcast(bIsActivated);
}

AItemBase* UInventoryComponent::GetActivatedItem()
{
	return Slots[ActivatedIndex].Item;
}

void UInventoryComponent::OnComponentDestroyed(bool bDestroyingHierarchy)
{
	Super::OnComponentDestroyed(bDestroyingHierarchy);

	for (auto& Slot : Slots)
	{
		if (IsValid(Slot.Item))
		{
			Slot.Item->Destroy();
		}
	}
	
	Slots.Empty();
}
