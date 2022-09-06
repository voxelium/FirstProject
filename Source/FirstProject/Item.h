// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraEmitter.h"
#include "GameFramework/Actor.h"

#include "Item.generated.h"

UCLASS()
class FIRSTPROJECT_API AItem : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AItem();
	
	//Базовая форма коллизий
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item | Overlap Collision")
	class USphereComponent* CollisionVolume;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item | Overlap Mesh")
	UStaticMeshComponent* Mesh;

	// 1 вариант использования частиц - как Component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item | Overlap Particles Idle")
	UParticleSystemComponent* IdleParticlesComponent;

	// 2 вариант использования частиц - как Систему частиц (Cascad)
	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item | Overlap Particles Spawn")
	// UParticleSystem* OverlapeParticles;

	// 2 вариант использования частиц - как Систему частиц (Niagara)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item | Overlap Particles Spawn")
	UNiagaraSystem * OverlapeParticles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item | Overlap Sound")
	class USoundCue* OverlapSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item | Overlap Rotation")
	bool bPikupRotate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item | Overlap Rotation")
	float RotationRate;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
