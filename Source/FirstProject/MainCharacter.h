// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

UCLASS()
class FIRSTPROJECT_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

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
	float BaseLookUp;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category=Camera);
	FRotator ClampCameraboomRotation;
	

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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
};
