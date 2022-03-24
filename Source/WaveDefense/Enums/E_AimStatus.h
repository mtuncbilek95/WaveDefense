// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "E_AimStatus.generated.h"

UENUM(BlueprintType)
enum E_AimStatus
{
	EAS_Freelook	UMETA(DisplayName = "Freelook"),
	EAS_Aiming		UMETA(DisplayName = "Aiming")
};