// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "E_BaseStatus.generated.h"

UENUM(BlueprintType)
enum E_BaseStatus
{
	EBS_NoWeapon	UMETA(DisplayName = "NoWeapon"),
	EBS_HaveWeapon	UMETA(DisplayName = "HaveWeapon")
};