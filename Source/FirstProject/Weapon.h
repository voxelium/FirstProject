// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Weapon.generated.h"

/**
 *  
 */
UCLASS()
class FIRSTPROJECT_API AWeapon : public AItem
{
	GENERATED_BODY()
	
public:
	
	AWeapon();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item | Particles")	
	bool bWeaponParticles;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item | Sound")
	USoundCue* OnEquipSound;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Skeletal Mesh")
	USkeletalMeshComponent* SkeletalMesh;

	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) override;
	
	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	//Экипирует персонажа оружием при пересечении
	void Equip (class AMainCharacter* Character);
	
};
