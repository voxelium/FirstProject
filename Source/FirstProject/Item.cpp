// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"

#include "MainCharacter.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Sound/SoundCue.h"



// Sets default values
AItem::AItem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CollisionVolume = CreateDefaultSubobject<USphereComponent>("Collision");
	RootComponent = CollisionVolume;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(GetRootComponent());

	//Система частиц для режима бездействия
	IdleParticlesComponent = CreateDefaultSubobject<UParticleSystemComponent>("Idle Particles");
	IdleParticlesComponent->SetupAttachment(GetRootComponent());

	//запрещает item вращаться
	bPikupRotate = false;
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	CollisionVolume->OnComponentBeginOverlap.AddDynamic(this, & AItem::OnOverlapBegin);
	CollisionVolume->OnComponentEndOverlap.AddDynamic(this, & AItem::OnOverlapEnd);
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(bPikupRotate)
	{
		FRotator Rotation = GetActorRotation();
		Rotation.Yaw += RotationRate;
		SetActorRotation(Rotation);
	}
}

void AItem::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Item Parent - Пересечение началось"));

	if (OtherActor)
	{
		AMainCharacter* Main = Cast<AMainCharacter>(OtherActor);

		if (Main)
		{
			if(OverlapeParticles)
			{
				// UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), OverlapeParticles, GetActorLocation(), FRotator(0.f), true);
				UNiagaraFunctionLibrary::SpawnSystemAtLocation (GetWorld(), OverlapeParticles, GetActorLocation(),
					FRotator(0.f), FVector(1.f), true, true,ENCPoolMethod::None, true);
			}

			if(OverlapSound)
			{
				UGameplayStatics::PlaySound2D(this, OverlapSound);
			}

			Destroy();
		}
		
	}
	
	
	
}

void AItem::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("Item Parent - Пересечение закончилось"));
}

