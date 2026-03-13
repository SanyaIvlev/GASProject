#include "DamageExecutionCalculation.h"
#include "GASProject/GAS/AttributeSets/HealthSet.h"

FDamageStatics::FDamageStatics()
{
	DEFINE_ATTRIBUTE_CAPTUREDEF(UHealthSet, ArmorHealth, Target, false)
	DEFINE_ATTRIBUTE_CAPTUREDEF(UHealthSet, ArmorAbsorption, Target, false);
	DEFINE_ATTRIBUTE_CAPTUREDEF(UHealthSet, Health, Target, false);
	DEFINE_ATTRIBUTE_CAPTUREDEF(UHealthSet, IncomingDamage, Target, false);
}

const FDamageStatics& UDamageExecutionCalculation::DamageStatics()
{
	static FDamageStatics Statics;
	return Statics;
}

UDamageExecutionCalculation::UDamageExecutionCalculation()
{
	RelevantAttributesToCapture.Add(DamageStatics().ArmorHealthDef);
	RelevantAttributesToCapture.Add(DamageStatics().ArmorAbsorptionDef);
	RelevantAttributesToCapture.Add(DamageStatics().HealthDef);
	RelevantAttributesToCapture.Add(DamageStatics().IncomingDamageDef);
}

void UDamageExecutionCalculation::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(DamageStatics().IncomingDamageProperty, EGameplayModOp::Override, 0));
	
	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
	
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags(); 
	
	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;
	
	FGameplayTagContainer AssetTags;
	Spec.GetAllAssetTags(AssetTags);
	
	float Damage;// = Spec.GetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("SetByCaller.HealthSet.IncomingDamage")), false, -1);
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().IncomingDamageDef, EvaluationParameters, Damage);
	// if (Damage == -1)
	// {
	// 	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().IncomingDamageDef, EvaluationParameters, Damage);
	// }
	
	if (AssetTags.HasTag(FGameplayTag::RequestGameplayTag(FName("GameplayEffect.Damage.BodyOnly"))))
	{
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(DamageStatics().HealthProperty, EGameplayModOp::Additive, -Damage));
		return;
	}
	
	float Armor;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorHealthDef, EvaluationParameters, Armor);
	
	float ArmorAbsorption;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorAbsorptionDef, EvaluationParameters, ArmorAbsorption);
	
	float Health;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().HealthDef, EvaluationParameters, Health);
	
	float ArmorDamageFinal = 0, HealthDamageFinal = 0;
	
	float ArmorAbsorbedDamage = Damage * ArmorAbsorption;
	
	if (ArmorAbsorbedDamage > Armor)
	{
		ArmorDamageFinal = Armor;
		float LeftDamage = ArmorAbsorbedDamage - Armor;
		HealthDamageFinal = LeftDamage;
	}
	else
	{
		ArmorDamageFinal = ArmorAbsorbedDamage;
		HealthDamageFinal = Damage - ArmorAbsorbedDamage; 
	}
	
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(DamageStatics().HealthProperty, EGameplayModOp::Additive, -HealthDamageFinal));
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(DamageStatics().ArmorHealthProperty, EGameplayModOp::Additive, -ArmorDamageFinal));
}
