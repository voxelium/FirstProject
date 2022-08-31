// Fill out your copyright notice in the Description page of Project Settings.


#include "MainAnimInstance.h"
#include "GameFramework/PawnMovementComponent.h"

// Подобие конструктора у Actor
void UMainAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (Pawn == nullptr)
	{
		Pawn = TryGetPawnOwner();
	}

	
}

//подобие Тика, для получения даных о состоянии персонажа в каждом кадре
void UMainAnimInstance::UpdateAnimationProperies()
{
	if (Pawn == nullptr)
	{
		Pawn = TryGetPawnOwner();
	}

	if (Pawn)
	{
		FVector Speed = Pawn->GetVelocity();
		FVector LateralSpeed = FVector(Speed.X, Speed.Y, 0.f);
		MovementSpeed = LateralSpeed.Size();

		bIsInAir = Pawn->GetMovementComponent()->IsFalling();
		
	}
	
}
