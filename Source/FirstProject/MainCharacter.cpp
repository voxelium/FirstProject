// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"

#include "Weapon.h"
#include "Camera/CameraActor.h"
#include "Camera/PlayerCameraManager.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//создание Spring Arm камеры
	Cameraboom = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	// Cameraboom->SetupAttachment(GetRootComponent());	// прикрепление Spring Arm к корневому объекту персонажа
	Cameraboom->SetupAttachment (GetRootComponent());	
	Cameraboom->TargetArmLength = 600.f; //  устанавливаем длину Spring Arm
	Cameraboom->SetWorldRotation(FRotator(-45.f,0.f,0.f));
	
	
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
	GetCharacterMovement()->JumpZVelocity = 550.f;
	// Контроль (управление) персонажа в воздухе
	GetCharacterMovement()->AirControl = 0.1f;
	
	
	//Устанавливаем размеры капсулы коллизии
	GetCapsuleComponent()->SetCapsuleSize(34.f, 90.f);
	
	//установка значений поворота камеры
	BaseTurnRate	= 65.f;

	// Player Stats Default
	Health =		0.65f;
	Damage =		0.1f;

	// выносливость Stamina
	StaminaStatus = EStaminaStatus::ESS_Normal;
	MaxStamina =	1.f;
	Stamina =		0.5f;
	StaminaDrainRate = 0.2f;
	MinSprintStamina = 0.50f;

	Coins =	0;

	//Ускорение
	MovementStatus = EMovementStatus::EMS_Normal;
	RunningSpeed = 550.f;
	SprintingSpeed = 750.f;
	bShiftKeyDown = false;

	bLMBDown = false;
	
}




// ------------------------------------------BEGIN PLAY----------------------------------
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	PlayerController->PlayerCameraManager->ViewPitchMin = -45.f;
	PlayerController->PlayerCameraManager->ViewPitchMax = 0.f;
	
	// Устанавливает ограничение для Pitch камеры с проверкой ссылки на PlayerController (более правильный вариант)
	 // PlayerController = Cast<APlayerController>(Controller);
	 // if (PlayerController)
	 // {
	 // 	if (PlayerController->PlayerCameraManager)
	 // 	{
	 // 		PlayerController->PlayerCameraManager->ViewPitchMin = -45.f;
	 // 		PlayerController->PlayerCameraManager->ViewPitchMax = 0.f;
	 // 	}
	 // }
	// Устанавливает Pitch поворот камеры в начале игры
	PlayerController->SetControlRotation(FRotator(0-20.f,0.f,0.f));


}

// ------------------------------------------TICK----------------------------------
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Stamina в единицу времени
	float DeltaStamina = StaminaDrainRate * DeltaTime;

	// Действия в зависимости от текущего статуса Stamina
	switch(StaminaStatus)
	{
	case EStaminaStatus::ESS_Normal:
		if(bShiftKeyDown)
		{
			if (Stamina - DeltaStamina <= MinSprintStamina)
			{
				SetStaminaStatus(EStaminaStatus::ESS_BelowMinimum);
				Stamina -= DeltaStamina;
			}
			else
			{
				Stamina -= DeltaStamina;
			}
			SetMovementStatus(EMovementStatus::EMS_Sprinting);
		}
		else // Shift key up
		{
			if(Stamina + DeltaStamina >= MaxStamina)
			{
				Stamina = MaxStamina;
			}
			else
			{
				Stamina += DeltaStamina;
			}
			SetMovementStatus(EMovementStatus::EMS_Normal);
		}
		break;
		
	case EStaminaStatus::ESS_BelowMinimum:
		if (bShiftKeyDown)
		{
			if (Stamina - DeltaStamina <= 0.f)
			{
				SetStaminaStatus(EStaminaStatus::ESS_Exhausted);
				Stamina = 0.f;
				SetMovementStatus(EMovementStatus::EMS_Normal);
			}
			else
			{
				Stamina -= DeltaStamina;
				SetMovementStatus(EMovementStatus::EMS_Sprinting);
			}
		}
		else // Shift released
		{
			if (Stamina+DeltaStamina >= MinSprintStamina)
			{
				SetStaminaStatus(EStaminaStatus::ESS_Normal);
				Stamina += DeltaStamina;
			}
			else
			{
				Stamina += DeltaStamina;
				SetStaminaStatus(EStaminaStatus::ESS_ExhaustedRecovery);
			}
			SetMovementStatus(EMovementStatus::EMS_Normal);
		}
		break;
		
	case EStaminaStatus::ESS_Exhausted:
		if (bShiftKeyDown)
		{
			Stamina = 0.f;
		}
		else // Shift released
			{
			Stamina += DeltaStamina;
			SetStaminaStatus(EStaminaStatus::ESS_ExhaustedRecovery);
			}
		SetMovementStatus(EMovementStatus::EMS_Normal);
		break;
		
	case EStaminaStatus::ESS_ExhaustedRecovery:
		if (Stamina + DeltaStamina >= MinSprintStamina)
		{
			SetStaminaStatus(EStaminaStatus::ESS_Normal);
			Stamina += DeltaStamina;
		}
		else // Shift released
			{
			 Stamina += DeltaStamina;
			}
		SetMovementStatus(EMovementStatus::EMS_Normal);
		break;
		
		default:
			;
	}


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

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AMainCharacter::ShiftKeyDown);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AMainCharacter::ShiftKeyUp);

	PlayerInputComponent->BindAction("LMB", IE_Pressed, this, &AMainCharacter::LMBDown);
	PlayerInputComponent->BindAction("LMB", IE_Released, this, &AMainCharacter::LMBUP);
	
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

//Устанавливает скорость поворота камеры влево/вправо
void AMainCharacter::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

//Устанавливает скорость движения камеры вверх/вниз
void AMainCharacter::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}


void AMainCharacter::LMBDown()
{
	bLMBDown = true;
	if(ActiveOverlappingItem)
	{
		AWeapon* Weapon = Cast<AWeapon>(ActiveOverlappingItem);
		if (Weapon)
		{
			Weapon->Equip(this);
			SetActiveOverlappingItem(nullptr);
		}
	}
}

void AMainCharacter::LMBUP()
{
	bLMBDown = false;
}

void AMainCharacter::SetEquippedWeapon(AWeapon* WeaponToSet)
{
	if(EquippedWeapon)
	{
		EquippedWeapon->Destroy();
	}

	EquippedWeapon = WeaponToSet;
}
 
void AMainCharacter::DecrementHealth(float Amount)
{
	if((Health - Amount) <= 0.f)
	{
		Health -= Amount;
		Die();
	}
	else
	{
		Health -= Amount;
	}

	
}

void AMainCharacter::IncrementCoins(int32 Amount)
{
	Coins = Coins + Amount;	
}

void AMainCharacter::Die()
{
}



void AMainCharacter::SetMovementStatus(EMovementStatus Status)
{
	MovementStatus = Status;
	if 	(MovementStatus == EMovementStatus::EMS_Sprinting)
	{
		GetCharacterMovement()->MaxWalkSpeed = SprintingSpeed;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = RunningSpeed;
	}

}

void AMainCharacter::ShiftKeyDown()
{
	bShiftKeyDown = true;
}

void AMainCharacter::ShiftKeyUp()
{
	bShiftKeyDown = false;
}

// Показывает расположение поднятых Pickup PickUp объектов
void AMainCharacter::ShowPickupLocations() const
{
	//Цикл для показа всех DrawDebugSphere в местах расположения поднятых Pickup объектов (версия 1)
	// for(int32 i = 0;
	// 	i < PickupLocations.Num();
	// 	i++)
	// {
	// 	UKismetSystemLibrary::DrawDebugSphere(this, PickupLocations[i], 25.f,8, FLinearColor::Green, 10.f, 0.5f);
	// }

	//Цикл для показа всех DrawDebugSphere в местах расположения поднятых Pickup объектов (версия 2)
	for (FVector Location : PickupLocations)
	{
		UKismetSystemLibrary::DrawDebugSphere(this, Location, 25.f,8, FLinearColor::Green, 10.f, 0.5f);
	}
}
