// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TankAIController.h"

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
    
    if(PlayerTank)
    {
        // aim towards player
        ControlledTank->AimAt(PlayerTank->GetActorLocation());
        //fire if/when ready
        ControlledTank->FireProjectile(); // TO DO limit firing rate
    }

}


