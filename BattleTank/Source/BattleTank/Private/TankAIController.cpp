// Fill out your copyright notice in the Description page of Project Settings.


#include "Kismet/GameplayStatics.h"
#include "TankAIController.h"


ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
    auto PlayerPawn{GetWorld()->GetFirstPlayerController()->GetPawn()};
    if(!PlayerPawn) { return nullptr; }
    return Cast<ATank>(PlayerPawn);
}



void ATankAIController::BeginPlay() 
{
	Super::BeginPlay();
	
    ATank* PlayerTank{GetPlayerTank()};
    if(PlayerTank)
    {
        UE_LOG(LogTemp, Warning, TEXT("Found FirstPlayerController: %s"), *(PlayerTank->GetName()));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Unable to FirstPlayerController from AItank"));
    }

}