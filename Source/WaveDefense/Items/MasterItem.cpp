// Fill out your copyright notice in the Description page of Project Settings.


#include "MasterItem.h"

#include "Kismet/KismetTextLibrary.h"

// Sets default values
AMasterItem::AMasterItem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	DefaultSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRootComponent"));
	RootComponent = DefaultSceneComponent;
}

// Called when the game starts or when spawned
void AMasterItem::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMasterItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMasterItem::OnInteract(AMasterCharacter* Player)
{
}

void AMasterItem::OnInteractEnter(AMasterCharacter* Player)
{
	
	if(IsValid(WidgetClass))
	{
		InteractionWidget = Cast<UInteractionWidget>(
			CreateWidget(Cast<APlayerController>(Player->GetController()),WidgetClass));
		InteractionComponent = NewObject<UWidgetComponent>(this);
		InteractionComponent->RegisterComponent();
		InteractionComponent->SetWidget(InteractionWidget);
		InteractionWidget->InteractWord = GetText("Interact");
		InteractionComponent->SetDrawAtDesiredSize(true);
		InteractionComponent->SetWidgetSpace(EWidgetSpace::Screen);
		InteractionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
		InteractionComponent->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
	
	}
	
}

void AMasterItem::OnInteractExit()
{
	if(IsValid(InteractionComponent))
	{
		InteractionComponent->DestroyComponent();
		InteractionComponent = nullptr;
		
	}
}

FText AMasterItem::GetText(FString text)
{
	return UKismetTextLibrary::Conv_StringToText(text);
}
