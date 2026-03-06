#include "DamageSet.h"

UDamageSet::UDamageSet() : BaseDamage(5.0f)
{
}

void UDamageSet::InitializeBaseDamage(float NewValue)
{
	if (NewValue > 0.0f)
	{
		SetBaseDamage(NewValue);
	}
}
