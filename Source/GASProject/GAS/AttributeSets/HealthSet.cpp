#include "HealthSet.h"
#include "GameplayEffectExtension.h"

UHealthSet::UHealthSet() : Health(100.0f), MaxHealth(100.0f)
{
	bIsOutOfHealth = false;
	MinHealth = 0.0f;
}

void UHealthSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
		
	// if (Attribute == GetHealthAttribute())
	// {
	// 	float NewHealth = FMath::Clamp(NewValue, MinHealth, GetMaxHealth());
	// 	SetHealth(NewHealth);
	// 	
	// 	if (NewHealth <= MinHealth && !bIsOutOfHealth)
	// 	{
	// 		OnOutOfHealth.Broadcast();
	// 		bIsOutOfHealth = true;
	// 	}
	// }
}

void UHealthSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	
		
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		float NewHealth = FMath::Clamp(GetHealth(), MinHealth, GetMaxHealth());
		SetHealth(NewHealth);
		
		if (NewHealth <= MinHealth && !bIsOutOfHealth)
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
