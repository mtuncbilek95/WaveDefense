// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WaveDefense/Enums/E_HandedWeaponType.h"
#include "WaveDefense/Enums/E_WeaponState.h"
#include "WeaponData.generated.h"

USTRUCT(BlueprintType)
struct FWeaponData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Data")
	FName GunName;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Data")
	TEnumAsByte<E_HandedWeaponType> HandedWeapon;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Data")
	TEnumAsByte<E_WeaponState> WeaponState;
	
};
