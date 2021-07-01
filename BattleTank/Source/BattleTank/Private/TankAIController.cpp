// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"

void ATankAIController::BeginPlay() 
{
	Super::BeginPlay();
	
}

// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    
    auto PlayerTank{Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn())};
    auto ControlledTank{Cast<ATank>(GetPawn())};
    
    if(ensure(PlayerTank))
    {
        // move towards player
        MoveToActor(PlayerTank, AcceptanceRadius); // TO DO check units of AcceptanceRadius

        // aim towards player
        ControlledTank->AimAt(PlayerTank->GetActorLocation());
        //fire if/when ready
        ControlledTank->FireProjectile(); // TO DO limit firing rate
    }

}


