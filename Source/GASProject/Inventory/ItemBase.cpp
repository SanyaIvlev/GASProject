#include "ItemBase.h"

AItemBase::AItemBase()
{
	PrimaryActorTick.bCanEverTick = false;
    ItemData = nullptr;
}
