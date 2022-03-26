// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "WaveDefense/Enums/E_AimStatus.h"
#include "WaveDefense/Enums/E_BaseStatus.h"
#include "WaveDefense/Enums/E_HandedWeaponType.h"
#include "WaveDefense/Enums/E_LocomotionStatus.h"
#include "MasterCharacter.generated.h"

class AMasterWeapon;

UCLASS()
class WAVEDEFENSE_API AMasterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMasterCharacter();

#pragma region "Components"

	UPROPERTY(Category=Components, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm;

	UPROPERTY(Category=Components, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(Category=Components, VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	AMasterWeapon* HandedWeapon;

#pragma endregion

#pragma region "State Enums"

	UPROPERTY(Category=CharacterData, VisibleAnywhere, BlueprintReadWrite)
	TEnumAsByte<E_LocomotionStatus> LocomotionStatus;

	UPROPERTY(Category=CharacterData, VisibleAnywhere, BlueprintReadWrite)
	TEnumAsByte<E_BaseStatus> BaseStatus;

	UPROPERTY(Category=CharacterData, VisibleAnywhere, BlueprintReadWrite)
	TEnumAsByte<E_AimStatus> AimStatus;

	UPROPERTY(Category=CharacterData, VisibleAnywhere, BlueprintReadWrite)
	TEnumAsByte<E_HandedWeaponType> HandedWeaponType;

#pragma endregion

#pragma region "Overlap Functions"
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// declare overlap end function
	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
#pragma endregion
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	bool debugger;
	
#pragma region "Direction and Rotation Variables"

	UFUNCTION(BlueprintPure)
	void ControllerRotation(FVector& ForwardVector, FVector& RightVector) const;

	UPROPERTY(Category=MovementData, VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	float MoveForward;

	UPROPERTY(Category=MovementData, VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	float MoveRight;

	UPROPERTY(Category=MovementData, VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	float TurnValue;

	UPROPERTY(Category=MovementData, VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	float LookValue;

	UFUNCTION(BlueprintCallable)
	void CalculateDirectionRotation();

	UPROPERTY(Category=AimData, VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	float DirectionYaw;

	UPROPERTY(Category=AimData, VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	float DirectionPitch;

	UPROPERTY(Category=AimData, VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	float DirectionRoll;

	UPROPERTY(Category=AimData, VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	float CameraYaw;

	UPROPERTY(Category=AimData, VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	float CameraPitch;

	UPROPERTY(Category=AimData, VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	float CameraRoll;

#pragma endregion

#pragma region "Camera Smoothening"

	UFUNCTION(BlueprintCallable)
	void AimCameraSmoothening();

#pragma endregion

#pragma region "Pick Up/Interact"

	UFUNCTION(BlueprintCallable, Category="Interaction")
	void Interact();
	
	UFUNCTION(BlueprintNativeEvent)
	void UpdateAttachment();
	
	UFUNCTION()
	void PickUpGun(AMasterWeapon* Weapon);

	UPROPERTY(Category=MovementData, VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	FString DebuggerString;
#pragma endregion 
};
