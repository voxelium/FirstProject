// Fill out your copyright notice in the Description page of Project Settings.


#include "MainAnimInstance.h"

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
void UMainAnimInstance::EUpdateAnimationProperies()
{
	
}
