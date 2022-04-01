// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "UObject/Interface.h"
#include "WeaponSystem.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UWeaponSystem : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class WAVEDEFENSE_API IWeaponSystem
{
	GENERATED_BODY()
	
	

public:
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category= "Weapon")
	void FireWeapon(UCameraComponent* PlayerCamera);
};
