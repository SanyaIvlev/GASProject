// Fill out your copyright notice in the Description page of Project Settings.


#include "DebugCommandsConfiguration.h"

const UDebugCommandsConfiguration* UDebugCommandsConfiguration::GetConfig()
{
	return GetDefault<UDebugCommandsConfiguration>();
}
