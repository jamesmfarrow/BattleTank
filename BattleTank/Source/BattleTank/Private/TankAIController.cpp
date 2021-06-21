// Fill out your copyright notice in the Description page of Project Settings.


#include "Kismet/GameplayStatics.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay() 
{
	Super::BeginPlay();
	
    ATank* PlayerTank{GetPlayerTank()};
    if(PlayerTank)
    {
        UE_LOG(LogTemp, Warning, TEXT("Found FirstPlayerController: %s"), *(PlayerTank->GetName()));
        PlayerTank->AimAt(PlayerTank->GetActorLocation());
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Unable to FirstPlayerController from AItank"));
    }

}

// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    //UE_LOG(LogTemp, Warning, TEXT("AIController is ticking"));
    
    if(GetPlayerTank())
    {
        //TODO move towards the player

        // aim towards player
        GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
        //fire if/when ready
    }

}

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


