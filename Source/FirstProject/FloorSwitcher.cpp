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

	// Создаем Mesh для Door
	Door = CreateDefaultSubobject<UStaticMeshComponent>("Door");
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
	
	
}

// Called every frame
void AFloorSwitcher::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFloorSwitcher::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlap Begin"));
}

void AFloorSwitcher::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlap END"));
}


