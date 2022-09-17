// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

//Энумератор для ускорения
UENUM(BlueprintType)
enum class EMovementStatus : uint8
{
	EMS_Normal		UMETA("Normal"),
	EMS_Sprinting	UMETA("Sprinting"),
	EMS_MAX			UMETA("DefaultMAX")
};

//Энумератор для выносливаости
UENUM(BlueprintType)
enum class EStaminaStatus : uint8
{
	ESS_Normal				UMETA("Normal"),
	ESS_BelowMinimum		UMETA("BelowMinimum"),
	ESS_Exhausted			UMETA("Exhausted"),
	ESS_ExhaustedRecovery	UMETA("Exhausted Recovery"),
	ESS_MAX					UMETA("DefaultMAX")
	
	
};

UCLASS()
class FIRSTPROJECT_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

	//-----------------------DEBUG items array-----------------
	TArray<FVector>PickupLocations;
	
	UFUNCTION(BlueprintCallable)
	void ShowPickupLocations() const;
	
	//----------------------- УСКОРЕНИЕ -----------------------

	// Энумератор статусов для ускорения
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Running")
	EMovementStatus MovementStatus;

	// Установливает статус движения и скорость
	void SetMovementStatus(EMovementStatus Status);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Running")
	float RunningSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Running")
	float SprintingSpeed;

	// Нажат или не нажат Left Shift
	bool bShiftKeyDown;

	//Запускает ускорение, когда Left Shift нажат
	void ShiftKeyDown();

	//Прекращает ускорение, когда Left Shift отпущен 
	void ShiftKeyUp();

	//----------------------- ВЫНОСЛИВОСТЬ -----------------------
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Stamina")
	EStaminaStatus StaminaStatus;

	FORCEINLINE void SetStaminaStatus (EStaminaStatus Status){StaminaStatus = Status;}

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Stamina")
	float StaminaDrainRate;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Stamina")
	float MinSprintStamina;

	
	//----------------------- VARIABLES -----------------------
	
	//Камера бум позиционирует камеры сзади игрока
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* Cameraboom;

	// камера следования
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	//Скорость поворота камеры влево/вправо
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;
	
	//Скорость поворота камеры вверх/вниз
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category=Camera);
	float BaseLookUpRate;
	


	//----------------------------------- Player Stats -----------------
	
	UPROPERTY (EditDefaultsOnly, BlueprintReadWrite, Category = "Player Stats")
	float Damage;

	UPROPERTY (EditDefaultsOnly, BlueprintReadWrite, Category = "Player Stats")
	float Health;

	UPROPERTY (EditDefaultsOnly, BlueprintReadWrite, Category = "Player Stats")
	float MaxStamina;

	UPROPERTY (EditDefaultsOnly, BlueprintReadWrite, Category = "Player Stats")
	float Stamina;

	UPROPERTY (EditDefaultsOnly, BlueprintReadWrite, Category = "Player Stats")
	int32 Coins;
	
//----------------------- FUNCTIONS -----------------------
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//функция движения вперед/назад
	void MoveForward(float Value);

	//функция движения в сторону
	void MoveRight(float Value);

	//скорость поворота в бок
	void TurnAtRate(float Rate);

	//скорость поворота вверх
	void LookUpAtRate(float Rate);

	//Getter for Spring Arm
	FORCEINLINE USpringArmComponent* GetCameraBoom() const {return Cameraboom;}

	//Getter for Camera
	FORCEINLINE UCameraComponent* GetFollow() const {return FollowCamera; }

	void DecrementHealth(float Amount);

	void IncrementCoins(int32 Amount);

	void Die();

	bool bLMBDown;
	void LMBDown();
	void LMBUP();
	

	//Применяет оружие с которым пересекается персонаж
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Item")
	class AWeapon* EquippedWeapon;

	void SetEquippedWeapon(AWeapon* WeaponToSet);

	//Применяет айтем с которым пересекается персонаж
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Item")
	class AItem* ActiveOverlappingItem;
	FORCEINLINE void SetActiveOverlappingItem(AItem* Item){ActiveOverlappingItem = Item;}

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Anims")
	bool bAttacking;
	
	void Attack();

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category="Anims")
	UAnimMontage* CombatMontage; 
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	
};
