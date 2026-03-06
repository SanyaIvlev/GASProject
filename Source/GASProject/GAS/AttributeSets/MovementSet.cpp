#include "MovementSet.h"

UMovementSet::UMovementSet() : Speed(600.0f)
{
	MinSpeed = 0.0f;
}

void UMovementSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	
	if (GetSpeed() < MinSpeed)
	{
		SetSpeed(MinSpeed);
	}
	
	OnSpeedChanged.Broadcast(GetSpeed());
	
}
