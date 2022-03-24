// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "E_LocomotionStatus.generated.h"

UENUM(BlueprintType)
enum E_LocomotionStatus
{
	ELS_Idle		UMETA(DisplayName = "Idle"),
	ELS_Walk		UMETA(DisplayName = "Walk"),
	ELS_Jog			UMETA(DisplayName = "Jog"),
	ELS_Sprint		UMETA(DisplayName = "Sprint")
};