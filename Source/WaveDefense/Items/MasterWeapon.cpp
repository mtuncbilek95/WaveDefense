// Fill out your copyright notice in the Description page of Project Settings.


#include "MasterWeapon.h"
//Set default values
AMasterWeapon::AMasterWeapon()
{
	PrimaryActorTick.bCanEverTick = false;
	WeaponBody = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon Body"));
	WeaponBody->SetupAttachment(GetRootComponent());

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->SetupAttachment(WeaponBody);
}

//When beginning to play
void AMasterWeapon::BeginPlay()
{
	Super::BeginPlay();
	SetWeaponState(EWS_Dropped);
}

// Interaction Interface's OnInteract function
void AMasterWeapon::OnInteract(AMasterCharacter* Player)
{
	Super::OnInteract(Player);
	SetWeaponState(EWS_Equipped);
	Player->PickUpGun(this);
}

// Set weapon's statement options if equipped or not.
void AMasterWeapon::SetWeaponState(const E_WeaponState WeaponState)
{
	WeaponData.WeaponState = WeaponState;

	switch (WeaponData.WeaponState)
	{
	case EWS_Equipped:
		Collision->SetCollisionProfileName(FName("NoCollision"));
		WeaponBody->SetSimulatePhysics(false);
		WeaponBody->SetCollisionProfileName(FName("NoCollision"));
		WeaponBody->ResetRelativeTransform();
		WeaponBody->SetRelativeTransform(HandTransform);
		break;

	case EWS_Dropped:
		Collision->SetCollisionProfileName(FName("OverlapAllDynamic"));
		WeaponBody->SetSimulatePhysics(true);
		WeaponBody->SetCollisionProfileName(FName("WeaponActor"));
		break;

	default: break;
	}
}
