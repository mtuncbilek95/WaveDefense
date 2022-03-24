// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "E_WeaponState.generated.h"

UENUM(BlueprintType)
enum E_WeaponState
{
	EWS_Dropped		UMETA(DisplayName = "Dropped"),
	EWS_Equipped	UMETA(DisplayName = "Equipped")
};