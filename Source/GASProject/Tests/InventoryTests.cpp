#include "../Inventory/InventoryComponent.h"
#include "../Inventory/InventoryItemData.h"
#include "Misc/AutomationTest.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FInventoryTest, "Inventory.BasicFunctions", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FInventoryTest::RunTest(const FString& Parameters)
{
    UInventoryComponent* Inventory = NewObject<UInventoryComponent>();
    Inventory->MaxSlots = 3;
    // Call BeginPlay manually to initialize slots since we are not in a real world
    // Or just set the num directly for testing
    Inventory->Slots.SetNum(3);

    UInventoryItemData* ItemA = NewObject<UInventoryItemData>();
    ItemA->ItemTag = FGameplayTag::RequestGameplayTag(FName("Item.Weapon.Pistol"), false);

    UInventoryItemData* ItemB = NewObject<UInventoryItemData>();
    ItemB->ItemTag = FGameplayTag::RequestGameplayTag(FName("Item.Potion.Health"), false);

    // Test Adding
    TestTrue("Should add first item", Inventory->AddItem(ItemA));
    TestTrue("Should add second item", Inventory->AddItem(ItemB));
    TestEqual("First slot should be ItemA", Inventory->Slots[0].ItemData, ItemA);
    TestEqual("Second slot should be ItemB", Inventory->Slots[1].ItemData, ItemB);
    TestTrue("Third slot should be empty", Inventory->Slots[2].IsEmpty());

    // Test Full Inventory
    UInventoryItemData* ItemC = NewObject<UInventoryItemData>();
    TestTrue("Should add third item", Inventory->AddItem(ItemC));
    TestFalse("Should not add fourth item", Inventory->AddItem(ItemC));

    // Test Removal
    TestTrue("Should remove ItemA by tag", Inventory->RemoveItemByTag(ItemA->ItemTag));
    TestTrue("First slot should be empty after removal", Inventory->Slots[0].IsEmpty());
    TestFalse("Second slot should still have ItemB", Inventory->Slots[1].IsEmpty());

    return true;
}
