// Fill out your copyright notice in the Description page of Project Settings.


#include "FloorSwitcher.h"

#include "Components/BoxComponent.h"

// Sets default values
AFloorSwitcher::AFloorSwitcher()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>("Trigger Box");

	// Делаем TriggerBox корневым компонентом
	RootComponent = TriggerBox;

	// Указываем тип коллизий - только пересечения. Без взаимодействий с физикой
	TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	// Тип коллизий для Trigger Box
	TriggerBox->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);

	// Запрещаем реагировать на ВСЕ типы коллизий, чтобы потом указать на какой канал нужно реагировать
	TriggerBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	// Указывваем на какой канал коллизий нужно реагировать и как
	TriggerBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	// Устанавливаем Размер Trigger Box
	TriggerBox->SetBoxExtent(FVector(62.f,62.f,32.f));
	
	// Создаем Mesh для Door
	Door = CreateDefaultSubobject<UStaticMeshComponent>("Door");
	Door->SetupAttachment(GetRootComponent());

	// Создаем Mesh для Floor Switcher
	FloorSwitcher = CreateDefaultSubobject<UStaticMeshComponent>("Floor Switcher");
	FloorSwitcher->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void AFloorSwitcher::BeginPlay()
{
	Super::BeginPlay();

	//указываем какая функция запустится при начале пересечения с TriggerBox
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AFloorSwitcher::OnOverlapBegin);

	//указываем какая функция запустится по окончанию пересечения с TriggerBox
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &AFloorSwitcher::OnOverlapEnd);

	//запоминаем положение двери
	DoorStartLocation = Door->GetComponentLocation();

	DoorTopPlace = 200.f;
}

// Called every frame
void AFloorSwitcher::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Реализация функции поднятия двери
void AFloorSwitcher::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	LowerSwitcher();
	RaiseDoor();
}

// Реализация функции опускания двери
void AFloorSwitcher::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	LowerDoor();
	RaiseSwitcher();
}

// обновляем положение двери
void AFloorSwitcher::UpdateDoorLocation(float Z)
{
	FVector NewLocation = DoorStartLocation;
	NewLocation.Z = Z;
	Door->SetWorldLocation(NewLocation);
}


