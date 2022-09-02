// Fill out your copyright notice in the Description page of Project Settings.


#include "FloorSwitcher.h"
#include "Components/BoxComponent.h"

// Sets default values
AFloorSwitcher::AFloorSwitcher()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = Root;
	TriggerBox = CreateDefaultSubobject<UBoxComponent>("Trigger Box");
	TriggerBox->SetRelativeLocation(FVector(0,0,0));
	TriggerBox->SetupAttachment(GetRootComponent());
	 
	// Делаем TriggerBox кор0невым компонентом
	// RootComponent = TriggerBox;
	
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

	//---------------------------------------Door-------------------------------
	// Создаем Mesh для Door
	Door = CreateDefaultSubobject<UStaticMeshComponent>("Door");
	Door->SetupAttachment(GetRootComponent());
	
	//---------------------------------------Button-------------------------------
	// Создаем Mesh для Button
	Button = CreateDefaultSubobject<UStaticMeshComponent>("Floor Switcher");
	Button->SetupAttachment(GetRootComponent());

	SwitchTime = 2.f;
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
	
	//запоминаем положение кнопки
	ButtonStartLocation = Button->GetComponentLocation();
	


}

// Called every frame
void AFloorSwitcher::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//--------------------------------- FUNCTIONS --------------------------

// Действия при начале пересечения
void AFloorSwitcher::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	bCharacterOnSwitch = true;
	LoweringButton();
	RaiseDoor();
}

// Действия при окончании пересечения
void AFloorSwitcher::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	bCharacterOnSwitch = false;
	GetWorldTimerManager().SetTimer(SwitchTimerHandle, this, &AFloorSwitcher::CloseDoor, SwitchTime);

}

// обновляем положение двери
void AFloorSwitcher::UpdateDoorLocation(float Z)
{
	FVector NewLocation = DoorStartLocation;
	NewLocation.Z = Z;
	Door->SetWorldLocation(NewLocation);
}

// обновляем положение кнопки
void AFloorSwitcher::UpdateButtonLocation(float Z)
{
	FVector NewLocation = ButtonStartLocation;
	NewLocation.Z = Z;
	Button->SetWorldLocation(NewLocation);
}

// Закрывание двери
void AFloorSwitcher::CloseDoor()
{
if (!bCharacterOnSwitch)
	{
	LowerDoor();
	RaiseButton();
	}

}