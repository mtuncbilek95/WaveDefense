// Fill out your copyright notice in the Description page of Project Settings.


#include "MasterWeapon.h"

AMasterWeapon::AMasterWeapon()
{
	PrimaryActorTick.bCanEverTick = false;
	WeaponBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon Body"));
	WeaponBody->SetupAttachment(GetRootComponent());

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->SetupAttachment(WeaponBody);
	
}

void AMasterWeapon::BeginPlay()
{
	Super::BeginPlay();
	SetWeaponState(EWS_Dropped);
}

void AMasterWeapon::OnInteract(AMasterCharacter* Player)
{
	Super::OnInteract(Player);
	Player->PickUpGun(this);
	SetWeaponState(EWS_Equipped);
}

void AMasterWeapon::SetWeaponState(E_WeaponState WeaponState)
{
	WeaponData.WeaponState = WeaponState;

	switch (WeaponData.WeaponState)
	{
	case EWS_Equipped:
		Collision->SetCollisionProfileName(FName("NoCollision"));
		WeaponBody->SetSimulatePhysics(false);
		WeaponBody->SetCollisionProfileName(FName("NoCollision"));
		// WeaponBody->ResetRelativeTransform();
		break;

	case EWS_Dropped:
		Collision->SetCollisionProfileName(FName("OverlapAllDynamic"));
		WeaponBody->SetSimulatePhysics(true);
		WeaponBody->SetCollisionProfileName(FName("WeaponActor"));
		break;

	default: break;
	}
}
