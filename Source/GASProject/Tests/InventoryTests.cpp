#include "../Inventory/InventoryComponent.h"
#include "../Inventory/InventoryItemData.h"
#include "../Inventory/ItemBase.h"
#include "Misc/AutomationTest.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FInventoryTest, "Inventory.BasicFunctions", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FInventoryTest::RunTest(const FString& Parameters)
{
    UInventoryComponent* Inventory = NewObject<UInventoryComponent>();
    Inventory->MaxSlots = 3;
    Inventory->Slots.SetNum(3);

    UInventoryItemData* ItemDataA = NewObject<UInventoryItemData>();
    ItemDataA->ItemTag = FGameplayTag::RequestGameplayTag(FName("Item.Weapon.Pistol"), false);

    UInventoryItemData* ItemDataB = NewObject<UInventoryItemData>();
    ItemDataB->ItemTag = FGameplayTag::RequestGameplayTag(FName("Item.Potion.Health"), false);

    AItemBase* ItemA = NewObject<AItemBase>();
    ItemA->ItemData = ItemDataA;

    AItemBase* ItemB = NewObject<AItemBase>();
    ItemB->ItemData = ItemDataB;

    // Test Adding
    TestTrue("Should add first item", Inventory->AddItem(ItemA));
    TestTrue("Should add second item", Inventory->AddItem(ItemB));
    TestEqual("First slot should be ItemA", Inventory->Slots[0].Item, ItemA);
    TestEqual("Second slot should be ItemB", Inventory->Slots[1].Item, ItemB);
    TestTrue("Third slot should be empty", Inventory->Slots[2].IsEmpty());

    // Test Full Inventory
    AItemBase* ItemC = NewObject<AItemBase>();
    TestTrue("Should add third item", Inventory->AddItem(ItemC));
    TestFalse("Should not add fourth item", Inventory->AddItem(ItemC));

    UE_LOG(LogTemp, Warning, TEXT("[DEBUG_LOG] ItemDataA Tag: %s"), *ItemDataA->ItemTag.ToString());
    UE_LOG(LogTemp, Warning, TEXT("[DEBUG_LOG] ItemA GetItemTag: %s"), *ItemA->GetItemTag().ToString());

    // Test Removal
    TestTrue("Should remove ItemA by tag", Inventory->RemoveItemByTag(ItemDataA->ItemTag));
    TestTrue("First slot should be empty after removal", Inventory->Slots[0].IsEmpty());
    TestFalse("Second slot should still have ItemB", Inventory->Slots[1].IsEmpty());

    return true;
}
