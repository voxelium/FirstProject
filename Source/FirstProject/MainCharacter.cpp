// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "Camera/CameraActor.h"
#include "Camera/PlayerCameraManager.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//создание Spring Arm камеры
	Cameraboom = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	Cameraboom->SetupAttachment(GetRootComponent());	// прикрепление Spring Arm к корневому объекту персонажа
	Cameraboom->TargetArmLength = 600.f; //  устанавливаем длину Spring Arm
	// Cameraboom->SetWorldRotation(FRotator(-60.f,0.f,0.f));
	
	
	// поворачивается вслед за контроллером Pawn. Я не понял на что это влияет
	Cameraboom->bUsePawnControlRotation = true; 

	//запрет вращать персонажа вместе с SpringArm. Вращается только Spring Arm.
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationPitch = false;

	
	//создание камеры
	FollowCamera = CreateDefaultSubobject<UCameraComponent>("Camera");
	FollowCamera->SetupAttachment(Cameraboom, USpringArmComponent::SocketName); // крепим камеру к SpringArm
	// FollowCamera->bUsePawnControlRotation = false; // запрещает пешке Pawn поворачиваться за SpringArm

	
	// Персонаж поворачивается в направлении движения влево/вправо
	GetCharacterMovement()->bOrientRotationToMovement = true;
	// Скорость поворачивания персонажа
	GetCharacterMovement()->RotationRate = FRotator(0.0f,540.f,0.0f);
	// Скорость прыжка персонажа
	GetCharacterMovement()->JumpZVelocity = 650.f;
	// Контроль (управление) персонажа в воздухе
	GetCharacterMovement()->AirControl = 0.2f;
	
	//Устанавливаем размеры капсулы коллизии
	GetCapsuleComponent()->SetCapsuleSize(34.f, 90.f);
	
	//установка значений поворота камеры
	BaseTurnRate	= 65.f;
	BaseLookUp		= -45.f;


}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Устанавливает ограничение для Pitch rotation камеры без проверки ссылки на PlayerController
	PlayerController = Cast<APlayerController>(Controller);
	PlayerController->PlayerCameraManager->ViewPitchMin = -45.f;
	PlayerController->PlayerCameraManager->ViewPitchMax = 0.f;
	
	// Устанавливает ограничение для Pitch камеры с проверкой ссылки на PlayerController
	 // PlayerController = Cast<APlayerController>(Controller);
	 // if (PlayerController)
	 // {
	 // 	if (PlayerController->PlayerCameraManager)
	 // 	{
	 // 		PlayerController->PlayerCameraManager->ViewPitchMin = -45.f;
	 // 		PlayerController->PlayerCameraManager->ViewPitchMax = 0.f;
	 // 	}
	 // }
	
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check (PlayerInputComponent);

	//Входные сигналы для управления персонажем
	PlayerInputComponent->BindAxis("MoveForward",	this, &AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight",		this, &AMainCharacter::MoveRight);
	
	PlayerInputComponent->BindAxis("Turn",			this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp",		this, &APawn::AddControllerPitchInput);
	
	PlayerInputComponent->BindAxis("TurnRate",		this, &AMainCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUpRate",	this, &AMainCharacter::LookUpAtRate);
	
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	
}

void AMainCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// переменная поворота игрока
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation (0.f, Rotation.Yaw, 0.f);

		/* Присваиваем направление вращения по оси Yaw к локальной оси X матрицы вращения
		рассматривай матрицу вращения как виджет локальных направлений объекта */
		
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value); 
	}
}

void AMainCharacter::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// переменная поворота игрока
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation (0.f, Rotation.Yaw, 0.f);

		//Присваиваем направление вращения по оси Yaw к локальной оси Y матрицы вращения
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void AMainCharacter::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AMainCharacter::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUp * GetWorld()->GetDeltaSeconds());
}


