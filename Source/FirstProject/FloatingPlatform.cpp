// Fill out your copyright notice in the Description page of Project Settings.


#include "FloatingPlatform.h"


// Sets default values
AFloatingPlatform::AFloatingPlatform()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;
	StartPoint = FVector(0.f);
	EndPoint = FVector(50.f);
	InterpSpeed = 0.2f;
	bInterping = false;
	InterpTime = 2.f;

}

// Called when the game starts or when spawned
void AFloatingPlatform::BeginPlay()
{
	Super::BeginPlay();

	StartPoint = GetActorLocation();
	EndPoint += StartPoint;
	Distance = (EndPoint - StartPoint).Size();
	//включение таймера 
	GetWorldTimerManager().SetTimer(InterpTimer, this, &AFloatingPlatform::ToggleInterping, InterpTime);
}

// Called every frame
void AFloatingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


		// перемещает актора между точками инетерполяции
		FVector CurrentLocation = GetActorLocation();
		FVector Interp = FMath::VInterpTo(CurrentLocation, EndPoint, DeltaTime, InterpSpeed);
		SetActorLocation(Interp);

		// проверяет пора ли изменить точки интерполяции местами
		float DistanceTraveled = (GetActorLocation() - StartPoint).Size();
		if (Distance - DistanceTraveled <= 1.f)
		{
			ToggleInterping();
			GetWorldTimerManager().SetTimer(InterpTimer, this, &AFloatingPlatform::ToggleInterping, InterpTime);
			SwapVectors (StartPoint,EndPoint);
			ToggleInterping();

		}
	
}

void AFloatingPlatform::ToggleInterping()
{
	// Переключение bool
	bInterping = !bInterping;
}

// Смена значений векторов VecOne и VecTwo местами
void AFloatingPlatform::SwapVectors(FVector& VecOne, FVector& VecTwo)
{
	FVector Temp = VecOne;
	VecOne = VecTwo;
	VecTwo = Temp;
}


