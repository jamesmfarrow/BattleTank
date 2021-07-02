// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"


void ATankAIController::BeginPlay() 
{
	Super::BeginPlay();
	
}

// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    
    auto PlayerTank{GetWorld()->GetFirstPlayerController()->GetPawn()};
    auto ControlledTank{GetPawn()};
    
    if(!ensure(PlayerTank && ControlledTank)) return;
    // move towards player
    MoveToActor(PlayerTank, AcceptanceRadius); // TO DO check units of AcceptanceRadius

     // aim towards player
    auto AimingComponent{ControlledTank->FindComponentByClass<UTankAimingComponent>()};
    if(!ensure(AimingComponent)) return;
    AimingComponent->AimAt(PlayerTank->GetActorLocation());
    //fire if/when ready

    AimingComponent->FireProjectile(); // TODO limit firing rate

}


