// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAnimInstance.h"

#include "Enemy.h"

void UEnemyAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	GetEnemy();
}



void UEnemyAnimInstance::UpdateAnimationProperties()
{
	GetEnemy();

	FVector Speed = Pawn->GetVelocity();
	FVector LateralSpeed = FVector(Speed.X, Speed.Y, 0.f);
	MovementSpeed = LateralSpeed.Size();
}


// Получает ссылку на Enemy
void UEnemyAnimInstance::GetEnemy()
{
	if (Pawn == nullptr)
	{
		Pawn = TryGetPawnOwner();
		if(Pawn)
		{
			Enemy = Cast<AEnemy>(Pawn);
		}
	}
}