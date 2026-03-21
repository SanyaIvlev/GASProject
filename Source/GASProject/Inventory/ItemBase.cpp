#include "ItemBase.h"
#include "GameFramework/Character.h"
#include "GASProject/GAS/AbilitySet.h"

AItemBase::AItemBase()
{
	PrimaryActorTick.bCanEverTick = false;
    ItemData = nullptr;
}

void AItemBase::ProcessActivation(bool bIsActivated)
{
	SetActorHiddenInGame(!bIsActivated);
	
	TSubclassOf<UAnimInstance> ActivationAnimInstance = ItemData->ActivationAnimInstance;
	
	if (!IsValid(ActivationAnimInstance))
	{
		return;
	}
	
	if (ItemOwner == nullptr)
	{
		return;
	}
	
	UAnimInstance* OwnerAnimInstance = ItemOwner->GetMesh()->GetAnimInstance();
	
	if (!IsValid(OwnerAnimInstance))
	{
		return;
	}
	
	UAbilitySet* Abilities = ItemData->AbilitySet;
	
	if (bIsActivated)
	{
		OwnerAnimInstance->LinkAnimClassLayers(ActivationAnimInstance);
			
		if (IsValid(Abilities))
		{
			Abilities->GiveAbilities(ItemOwner);
		}
	}
	else
	{
		OwnerAnimInstance->UnlinkAnimClassLayers(ActivationAnimInstance);
		
		if (IsValid(Abilities))
		{
			Abilities->RemoveAbilities(ItemOwner);
		}
	}
}

void AItemBase::SetItemOwner(AAbilityCharacter* NewOwner)
{
	ItemOwner = NewOwner;
	OnOwnerUpdated.Broadcast(NewOwner);
}
