// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WaveDefense/Character/MasterCharacter.h"
#include "InteractionInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractionInterface : public UInterface
{
	GENERATED_BODY()
};

class WAVEDEFENSE_API IInteractionInterface
{
	GENERATED_BODY()

public:
	
	UFUNCTION()
	virtual void OnInteract(AMasterCharacter* Player) = 0;
	UFUNCTION()
	virtual void OnInteractEnter(AMasterCharacter* Player) = 0;
	UFUNCTION()
	virtual void OnInteractExit() = 0;
};
