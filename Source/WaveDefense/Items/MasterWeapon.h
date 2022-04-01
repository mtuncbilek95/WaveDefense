// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MasterItem.h"
#include "Components/SphereComponent.h"
#include "WaveDefense/Interfaces/WeaponSystem.h"
#include "WaveDefense/Structs/WeaponData.h"
#include "MasterWeapon.generated.h"

/**
 * 
 */
UCLASS()
class WAVEDEFENSE_API AMasterWeapon : public AMasterItem, public IWeaponSystem
{
	GENERATED_BODY()
public:
	AMasterWeapon();

	UPROPERTY(Category=Components, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	USkeletalMeshComponent* WeaponBody;

	UPROPERTY(Category=Components, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	USphereComponent* Collision;
	
protected:
	
	virtual void BeginPlay() override;
	
public:
	
	virtual void OnInteract(AMasterCharacter* Player) override;

	UFUNCTION()
	void SetWeaponState(E_WeaponState WeaponState);
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category= "Data")
	FWeaponData WeaponData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Data")
	FTransform HandTransform;

	virtual void FireWeapon_Implementation(UCameraComponent* PlayerCamera) override;
};
