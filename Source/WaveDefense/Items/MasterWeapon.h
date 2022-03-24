// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MasterItem.h"
#include "WaveDefense/Structs/WeaponData.h"
#include "MasterWeapon.generated.h"

/**
 * 
 */
UCLASS()
class WAVEDEFENSE_API AMasterWeapon : public AMasterItem
{
	GENERATED_BODY()
public:
	AMasterWeapon();

	virtual void OnInteract(AMasterCharacter* Player) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category= "Weapon Data")
	FWeaponData WeaponData;
};
