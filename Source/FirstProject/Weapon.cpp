// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "MainCharacter.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

AWeapon::AWeapon()
{
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Skeletal Mesh");
	SkeletalMesh->SetupAttachment(GetRootComponent());
}


//Начало пересечения
void AWeapon::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlapBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	if (OtherActor)
	{
		// 1. Вариант экипировки персонажа оружием. При начале пересечения.
		// AMainCharacter* Character = Cast<AMainCharacter>(OtherActor);
		// if (Character)
		// {
		// 	Equip(Character);
		// }

		// 2. Вариант экипировки персонажа оружием.
		AMainCharacter* Character = Cast<AMainCharacter>(OtherActor);
		if (Character)
		{
			Character->SetActiveOverlappingItem(this);
		}
		 
	}
}

//Конец Пересечения
void AWeapon::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	Super::OnOverlapEnd(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);

	// 2. Вариант экипировки персонажа оружием.
	AMainCharacter* Character = Cast<AMainCharacter>(OtherActor);
	if (Character)
	{
		Character->SetActiveOverlappingItem(nullptr);
	}
}

//Экипирует персонажа оружием
void AWeapon::Equip(AMainCharacter* Character)
{
	if(Character)
	{
//Устанавливает Ignore для канала коллизий Camera, чтобы камера не приближалась к персонажу, если меч окажется между персонажем и камерой
		SkeletalMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
		SkeletalMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
		SkeletalMesh->SetSimulatePhysics(false);

		// ссылка на сокет правой руки персонажа
		const USkeletalMeshSocket* RightHandSocket = Character->GetMesh()->GetSocketByName("RightHandSocket");
		if(RightHandSocket)
		{
			RightHandSocket->AttachActor(this, Character->GetMesh());
			bPikupRotate = false;
			Character->SetEquippedWeapon(this);
		}
		if(OnEquipSound)
		{
			UGameplayStatics::PlaySound2D(this, OnEquipSound);	
		}
	}
	
}
