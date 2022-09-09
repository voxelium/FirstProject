// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class FIRSTPROJECT_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	// Reference (ссылка) на ассет UMG в редакторе
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Widgets")
	TSubclassOf<UUserWidget> HUDOverlayAsset;

	// Переменная для хранения виджета HUD после его создания
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Widgets")
	UUserWidget* HUDOverlay;
	
protected:
	virtual void BeginPlay() override;

	
};
