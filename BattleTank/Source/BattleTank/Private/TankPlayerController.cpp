// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay() 
{
	Super::BeginPlay();
	
	ATank* MyTank{GetControlledTank()};
	if(MyTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank is possessed: %s"), *(MyTank->GetName()));

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No possessed tank"));
		
	}
}


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

