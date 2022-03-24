// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractionWidget.generated.h"

/**
 * 
 */
UCLASS()
class WAVEDEFENSE_API UInteractionWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(Category=Text, EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn="true"))
	FText InteractWord;
	
protected:
	UPROPERTY(meta = (BindWidget))
	class USizeBox* MainSizeBox;

	UPROPERTY(meta = (BindWidget))
	class UUniformGridPanel* Panel;

	UPROPERTY(meta = (BindWidget))
	class UHorizontalBox* MainBox;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextKeyFrame;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* InteractionWord;

	UPROPERTY(meta = (BindWidget))
	class UBorder* BackBorder;
};
