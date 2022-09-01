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

	// Объем для пересечения, запускающий какой-то функционал. Невидимый
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Floor Switcher")
	class UBoxComponent* TriggerBox;

	// Mesh - Отображение trigger box в мире
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Floor Switcher")
	UStaticMeshComponent* FloorSwitcher;

	// Mesh - срабатывающий после срабатывания Trigger Box
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Floor Switcher")
	UStaticMeshComponent* Door;

	// Исходное положение двери
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Floor Switcher")
	FVector DoorStartLocation;

	// Высота поднятия двери
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Floor Switcher")
	float DoorTopPlace;
	
	// Исходное положение кнопки
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Floor Switcher")
	FVector SwitcherStartLOcation;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// функция запустится при начале пересечения
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	// функция запустится по окончанию пересечения
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// Объявление функции Поднятия двери
	UFUNCTION(BlueprintImplementableEvent, Category= "Floor Switch")
	void RaiseDoor();

	// Объявление функции Опускания двери
	UFUNCTION(BlueprintImplementableEvent, Category= "Floor Switch")
	void LowerDoor();

	//Функция поднятия кнопки
	UFUNCTION(BlueprintImplementableEvent, Category= "Floor Switch")
	void RaiseSwitcher();

	//Функция опускания кнопки
	UFUNCTION(BlueprintImplementableEvent, Category= "Floor Switch")
	void LowerSwitcher();

	//обновление положения
	UFUNCTION(BlueprintCallable, Category= "Floor Switch")
	void UpdateDoorLocation(float Z);
	
};
