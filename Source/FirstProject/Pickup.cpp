// Fill out your copyright notice in the Description page of Project Settings.

#include "Pickup.h"
#include "MainCharacter.h"


APickup::APickup()
{
	CoinCollect = 1;
}

void APickup::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	Super::OnOverlapEnd(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
	UE_LOG(LogTemp, Warning, TEXT ("Pickup - Начало пересечения"));
	
		if(OtherActor)
    	{
    		AMainCharacter* Main = Cast<AMainCharacter>(OtherActor);
    		if(Main)
    		{
    			Main->IncrementCoins(CoinCollect);
    		}
    	}
}


void APickup::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                             UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlapBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	UE_LOG(LogTemp, Warning, TEXT("Pickup - Конец пересечения"));
}
