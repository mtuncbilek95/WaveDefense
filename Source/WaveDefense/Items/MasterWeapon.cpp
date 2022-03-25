// Fill out your copyright notice in the Description page of Project Settings.


#include "MasterWeapon.h"

AMasterWeapon::AMasterWeapon()
{

	WeaponBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon Body"));
	WeaponBody->SetupAttachment(GetRootComponent());

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->SetupAttachment(WeaponBody);
	
	WeaponData.WeaponState = EWS_Dropped;
	
}

void AMasterWeapon::BeginPlay()
{
	Super::BeginPlay();
	SetWeaponState(EWS_Dropped);
}

void AMasterWeapon::OnInteract(AMasterCharacter* Player)
{
	Super::OnInteract(Player);
	SetWeaponState(EWS_Equipped);
}

void AMasterWeapon::SetWeaponState(E_WeaponState WeaponState)
{
	WeaponData.WeaponState = WeaponState;

	switch(WeaponData.WeaponState)
	{
	case EWS_Equipped:
		Collision->SetCollisionProfileName("NoCollision");
		WeaponBody->SetSimulatePhysics(false);
		WeaponBody->SetCollisionProfileName("NoCollision");
		WeaponBody->ResetRelativeTransform();
		break;
	case EWS_Dropped:
		Collision->SetCollisionProfileName("OverlapAllDynamic");
		WeaponBody->SetSimulatePhysics(true);
		WeaponBody->SetCollisionProfileName("WeaponActor");
		break;
	default: break;
	}
}
