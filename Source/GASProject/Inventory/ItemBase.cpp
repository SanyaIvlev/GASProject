#include "ItemBase.h"
#include "GameFramework/Character.h"

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
	
	if (bIsActivated)
	{
		OwnerAnimInstance->LinkAnimClassLayers(ActivationAnimInstance);
	}
	else
	{
		OwnerAnimInstance->UnlinkAnimClassLayers(ActivationAnimInstance);
	}
}

void AItemBase::SetItemOwner(ACharacter* NewOwner)
{
	ItemOwner = NewOwner;
}
