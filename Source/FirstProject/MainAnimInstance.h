// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MainAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class FIRSTPROJECT_API UMainAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:

	virtual void NativeInitializeAnimation() override;

	UFUNCTION(BlueprintCallable, Category=AnimationProperties)
	void UpdateAnimationProperies();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement")
	float MovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement")
	bool bIsInAir;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement")
	APawn* Pawn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement")
	class AMainCharacter* Main;
	
};
