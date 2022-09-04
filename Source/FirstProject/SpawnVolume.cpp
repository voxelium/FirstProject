// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnVolume.h"
#include "Components/BoxComponent.h"
#include "Critter.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
ASpawnVolume::ASpawnVolume()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SpawningBox = CreateDefaultSubobject<UBoxComponent>("Spawning Box");
		 
		
}

// Called when the game starts or when spawned
void ASpawnVolume::BeginPlay()
{
	Super::BeginPlay();
	
}

//-------------------------------FUNCS ---------------
// Called every frame
void ASpawnVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//получает точку в пространстве Spawn Volume
FVector ASpawnVolume::GetSpawnPoint()
{
	//получает размер нашего Volume
	FVector Extent = SpawningBox->GetScaledBoxExtent();
	//получает центр объекта Volume
	FVector Origin = SpawningBox->GetComponentLocation();
	//получает случайную точку в пространстве Spawn Volume
	FVector Point = UKismetMathLibrary::RandomPointInBoundingBox(Origin, Extent);
	return Point;
}

void ASpawnVolume::SpawnOurPawn_Implementation(UClass* ToSpawn, const FVector& Location)
{
	if (ToSpawn)
	{
		UWorld* World = GetWorld();
		FActorSpawnParameters SpawnParams;	
		
		if (World)
		{
			ACritter* ActorSpawned = World->SpawnActor<ACritter>(ToSpawn, Location, FRotator(0.f), SpawnParams); 
		}
	}
}



