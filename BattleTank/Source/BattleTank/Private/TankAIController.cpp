// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h" //so we can implement onDeath()
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
    
    if(!(PlayerTank && ControlledTank)) return;
    // move towards player
    MoveToActor(PlayerTank, AcceptanceRadius); // TO DO check units of AcceptanceRadius

     // aim towards player
    auto AimingComponent{ControlledTank->FindComponentByClass<UTankAimingComponent>()};
    if(!ensure(AimingComponent)) return;
    AimingComponent->AimAt(PlayerTank->GetActorLocation());
   
   //fire if loacked
   if(AimingComponent->GetFiringState() == EFiringState::Locked)
    {
        AimingComponent->FireProjectile();
    }
}

void ATankAIController::SetPawn(APawn* InPawn) 
{
	Super::SetPawn(InPawn);
    if(InPawn)
    {
        auto PossessedTank{Cast<ATank>(InPawn)};
        if(!ensure(PossessedTank)) return;
        //subsribe our local method to Tank death event
        PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPssessedTankDeath);
    }
}

void ATankAIController::OnPssessedTankDeath() 
{
	UE_LOG(LogTemp, Warning, TEXT("Received!! AI"));
    auto PossessedTank{Cast<ATank>(GetPawn())};
    if(!ensure(PossessedTank)) return;
    PossessedTank->DetachFromControllerPendingDestroy();
}


