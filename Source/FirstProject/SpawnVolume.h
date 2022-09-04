// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnVolume.generated.h"

UCLASS()
class FIRSTPROJECT_API ASpawnVolume : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASpawnVolume();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawn")
	class UBoxComponent* SpawningBox;

	//Объявляется класс для спавна в Swan Volume
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawn")
	TSubclassOf<APawn>ActorToSpawn;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// ---------------- FUNCS --------------
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION (BlueprintPure, Category = "Spawn")
	FVector GetSpawnPoint();

	//Вариант спавна Actor через C++
	UFUNCTION (BlueprintNativeEvent, BlueprintCallable, Category = "Spawn")
	void SpawnOurPawn(UClass* ToSpawn, const FVector& Location);
	
};

	







