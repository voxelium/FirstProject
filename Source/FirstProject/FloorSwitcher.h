// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloorSwitcher.generated.h"

UCLASS()
class FIRSTPROJECT_API AFloorSwitcher : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloorSwitcher();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// Объем для пересечения, запускающий какой-то функционал. Невидимый
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Floor Switcher")
	class UBoxComponent* TriggerBox;

	// Mesh - Отображение trigger box в мире
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Floor Switcher")
	UStaticMeshComponent* Button;

	// Mesh - срабатывающий после срабатывания Trigger Box
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Floor Switcher")
	UStaticMeshComponent* Door;
	
	// функция запустится при начале пересечения
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	// функция запустится по окончанию пересечения
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	//---------------------Door----------------------
	// Объявление функции Поднятия двери
	UFUNCTION(BlueprintImplementableEvent, Category= "Floor Switch")
	void RaiseDoor();

	// Объявление функции Опускания двери
	UFUNCTION(BlueprintImplementableEvent, Category= "Floor Switch")
	void LowerDoor();

	//обновление положения двери
	UFUNCTION(BlueprintCallable, Category= "Floor Switch")
	void UpdateDoorLocation(float Z);

	// Исходное положение двери
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Floor Switcher")
	FVector DoorStartLocation;

	// Высота поднятия двери
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Floor Switcher")
	float DoorEndPlace;
	
	
	//---------------------Button----------------------
	// Исходное положение кнопки
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Floor Switcher")
	FVector ButtonStartLocation;
	
	// Высота опускания кнопки
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Floor Switcher")
	float ButtonEndPlace;
	
	//Функция поднятия кнопки
	UFUNCTION(BlueprintImplementableEvent, Category= "Floor Switch")
	void RaiseButton();

	//Функция опускания кнопки
	UFUNCTION(BlueprintImplementableEvent, Category= "Floor Switch")
	void LoweringButton();
	
	//обновление положения кнопки
	UFUNCTION(BlueprintCallable, Category= "Floor Switch")
	void UpdateButtonLocation(float Z);

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
