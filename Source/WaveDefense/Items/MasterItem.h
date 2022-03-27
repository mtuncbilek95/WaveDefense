// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Actor.h"
#include "WaveDefense/Interfaces/InteractionInterface.h"
#include "WaveDefense/Widget/InteractionWidget.h"
#include "MasterItem.generated.h"

UCLASS()
class WAVEDEFENSE_API AMasterItem : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMasterItem();
	
	UPROPERTY(Category=Components, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	USceneComponent* DefaultSceneComponent;
	
	UPROPERTY(EditAnywhere, Category="UI")
	TSubclassOf<UUserWidget> WidgetClass;

	UPROPERTY()
	UInteractionWidget* InteractionWidget;
	
	UPROPERTY()
	UWidgetComponent* InteractionComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnInteract(AMasterCharacter* Player) override;

	virtual void OnInteractEnter(AMasterCharacter* Player) override;

	virtual void OnInteractExit() override;

	UFUNCTION(BlueprintPure)
	static FText GetText(FString Text);
};
