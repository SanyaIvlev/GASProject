#include "HealthSet.h"
#include "GameplayEffectExtension.h"

UHealthSet::UHealthSet() : Health(100.0f), MaxHealth(100.0f)
{
	bIsOutOfHealth = false;
	MinHealth = 0.0f;
}

void UHealthSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	
	if (Data.EvaluatedData.Attribute == GetIncomingDamageAttribute() && !bIsOutOfHealth)
	{
		float NewHealth = FMath::Clamp(GetHealth() - GetIncomingDamage(), MinHealth, GetMaxHealth());
		SetHealth(NewHealth);
		SetIncomingDamage(0.0f);
		
		if (NewHealth <= MinHealth)
		{
			OnOutOfHealth.Broadcast();
			bIsOutOfHealth = true;
		}
	}
	else if (Data.EvaluatedData.Attribute == GetHealingAttribute() && !bIsOutOfHealth)
	{
		float NewHealth = FMath::Clamp(GetHealth() + GetHealing(), MinHealth, GetMaxHealth());
		SetHealth(NewHealth);
		SetHealing(0.0f);
	}
}
