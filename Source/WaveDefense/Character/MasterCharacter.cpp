// Fill out your copyright notice in the Description page of Project Settings.


#include "MasterCharacter.h"

#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "WaveDefense/Interfaces/InteractionInterface.h"
#include "WaveDefense/Items/MasterWeapon.h"

// Sets default values
AMasterCharacter::AMasterCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 250.0f;
	SpringArm->SocketOffset = FVector(0, 75, 0);
	SpringArm->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
	FollowCamera->SetFieldOfView(85);

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0, 500, 0);

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AMasterCharacter::OnOverlapBegin);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &AMasterCharacter::OnOverlapEnd);
}

void AMasterCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                      UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                      const FHitResult& SweepResult)
{

	if (IsValid(OtherActor))
	{
		IInteractionInterface* Interface = Cast<IInteractionInterface>(OtherActor);
		if(Interface)
		{
			Interface->OnInteractEnter(this);
		}

	}

}

void AMasterCharacter::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	IInteractionInterface* Interface = Cast<IInteractionInterface>(OtherActor);
	if (Interface)
	{
		Interface->OnInteractExit();
	}
}

// Called when the game starts or when spawned
void AMasterCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMasterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CalculateDirectionRotation();
	AimCameraSmoothening();
}

// Called to bind functionality to input
void AMasterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

#pragma region "Camera Controller"

//World rotation for "Add Movement Input"
void AMasterCharacter::ControllerRotation(FVector& ForwardVector, FVector& RightVector) const
{
	const float RotatorYaw = GetControlRotation().Yaw;
	const FRotator ControllerRotator = UKismetMathLibrary::MakeRotator(0, 0, RotatorYaw);

	ForwardVector = UKismetMathLibrary::GetForwardVector(ControllerRotator);
	RightVector = UKismetMathLibrary::GetRightVector(ControllerRotator);
}

//Change the direction according to movement input
void AMasterCharacter::CalculateDirectionRotation()
{
	const FRotator CameraRotator = UKismetMathLibrary::NormalizedDeltaRotator(
		FollowCamera->GetComponentRotation(), GetRootComponent()->GetComponentRotation());
	FVector const DirectionVector(MoveForward, -MoveRight, 0);
	const FRotator DirectionRotator = UKismetMathLibrary::MakeRotFromX(DirectionVector);

	UKismetMathLibrary::BreakRotator(CameraRotator, CameraRoll, CameraPitch, CameraYaw);

	const FRotator FinalRotator = UKismetMathLibrary::NormalizedDeltaRotator(CameraRotator, DirectionRotator);

	UKismetMathLibrary::BreakRotator(FinalRotator, DirectionRoll, DirectionPitch, DirectionYaw);

	DirectionYaw = UKismetMathLibrary::Round(DirectionYaw);
}

//Smooth transition between aiming and freelook.
void AMasterCharacter::AimCameraSmoothening()
{
	if (AimStatus == EAS_Aiming)
	{
		FollowCamera->FieldOfView = UKismetMathLibrary::FInterpTo(FollowCamera->FieldOfView,
		                                                          70, GetWorld()->DeltaTimeSeconds, 10);
		SpringArm->TargetArmLength = UKismetMathLibrary::FInterpTo(SpringArm->TargetArmLength,
		                                                           150, GetWorld()->DeltaTimeSeconds, 10);
	}

	else if (AimStatus == EAS_Freelook)
	{
		FollowCamera->FieldOfView = UKismetMathLibrary::FInterpTo(FollowCamera->FieldOfView,
		                                                          90, GetWorld()->DeltaTimeSeconds, 10);
		SpringArm->TargetArmLength = UKismetMathLibrary::FInterpTo(SpringArm->TargetArmLength,
		                                                           150, GetWorld()->DeltaTimeSeconds, 10);
		SpringArm->SocketOffset.Y = UKismetMathLibrary::FInterpTo(SpringArm->SocketOffset.Y,
		                                                          75, GetWorld()->DeltaTimeSeconds, 10);
	}
}

//Check all the overlapping actors, if the overlapping actors have Interaction Interface, call the OnInteract.
void AMasterCharacter::Interact()
{
	TArray<AActor*> Actors;
	
	GetCapsuleComponent()->GetOverlappingActors(Actors);
	
	for (const auto Actor : Actors)
	{
		IInteractionInterface* Interface = Cast<IInteractionInterface>(Actor);
		if(Interface)
		{
			Interface->OnInteract(this);
		}
		break;
	}
}

//Attach the weapons according to their position.
void AMasterCharacter::UpdateAttachment() const
{
	if(IsValid(HandedWeapon))
	{
		HandedWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("ik_hand_gun"));
	}
	if(IsValid(PrimaryWeapon))
	{
		PrimaryWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("back_socket"));
	}
	if(IsValid(SecondaryWeapon))
	{
		SecondaryWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("pocket_socket"));
	}
}

// Decide where to put the weapon on the ground, according to their type and your equip status.
void AMasterCharacter::PickUpGun(AMasterWeapon* Weapon)
{
	switch (Weapon->WeaponData.HandedWeapon)
	{
	case EHWT_Rifle: //Weapon on ground is rifle
		if(IsValid(HandedWeapon)) //Check hand first to see if there is a weapon in hand.
		{
			switch (HandedWeaponType) 
			{
			case EHWT_Rifle: //If holding rifle change the rifle.
				HandedWeapon->SetWeaponState(EWS_Dropped);
				HandedWeapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
				HandedWeapon = Weapon;
				UpdateAttachment();
				break;
				
			case EHWT_Pistol: //If holding pistol, check the rifle socket in back.
				if(IsValid(PrimaryWeapon)) //If there is a rifle in back, apply these below.
				{
					PrimaryWeapon->SetWeaponState(EWS_Dropped);
					PrimaryWeapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
					PrimaryWeapon = Weapon;
					UpdateAttachment();
				}
				else
				{
					PrimaryWeapon = Weapon;
					UpdateAttachment();
				}
				break;
				
			default: break;
			} 
		}
		else //If not holding a weapon, check the primary weapon.
		{
			if(IsValid(PrimaryWeapon)) //If there is a rifle in primary, change them.
			{
				PrimaryWeapon->SetWeaponState(EWS_Dropped);
				PrimaryWeapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
				PrimaryWeapon = Weapon;
				UpdateAttachment();
			}
			else //If there is no weapon in primary, hold the weapon.
			{
				HandedWeapon = Weapon;
				HandedWeaponType = HandedWeapon->WeaponData.HandedWeapon;
				UpdateAttachment();
			}
		}
		break;
		
	case EHWT_Pistol: //Weapon on ground is pistol
		break;
		
	default: break;
		
	}
}

#pragma endregion
