// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "E_HandedWeaponType.generated.h"

UENUM(BlueprintType)
enum E_HandedWeaponType
{
	EHWT_None	UMETA(DisplayName = "None"),
	EHWT_Rifle	UMETA(DisplayName = "Rifle"),
	EHWT_Pistol	UMETA(DisplayName = "Pistol")
};
