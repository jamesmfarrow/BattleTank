// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Tank.h" //so we can implement onDeath()

void ATankPlayerController::BeginPlay() 
{
	Super::BeginPlay();
	
	auto AimingComponent{GetPawn()->FindComponentByClass<UTankAimingComponent>()};
	if(!ensure(AimingComponent)) return;
	FoundAimingComponent(AimingComponent);
}


void ATankPlayerController::Tick(float DeltaTime) 
{

	Super::Tick(DeltaTime);
	AimAtCrossHairs();
}

void ATankPlayerController::SetPawn(APawn* InPawn) 
{
	Super::SetPawn(InPawn);
    if(InPawn)
    {
        auto PossessedTank{Cast<ATank>(InPawn)};
        if(!ensure(PossessedTank)) return;
        //subsribe our local method to Tank death event
        PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPssessedTankDeath);
    }
}

void ATankPlayerController::OnPssessedTankDeath() 
{
	UE_LOG(LogTemp, Warning, TEXT("Received!! Tank"));
}


void ATankPlayerController::AimAtCrossHairs() 
{
	if(!GetPawn()) return ; // e.g not possessing
	auto AimingComponent{GetPawn()->FindComponentByClass<UTankAimingComponent>()};
	if(!ensure(AimingComponent)) return;

	FVector HitLocation; //out parameter
	bool bGotHitLocation{GetSightHitRayLocation(HitLocation)};
	if(bGotHitLocation)
	{
		AimingComponent->AimAt(HitLocation);
	}

}

// get world location of linetrace through crosshair, true if it hits landscape
bool ATankPlayerController::GetSightHitRayLocation(FVector& HitLocation) const
{
	//find cross hair position in pixel co-ordinates
	int32 ViewPortSizeX, ViewPortSizeY;
	GetViewportSize(ViewPortSizeX, ViewPortSizeY); 
	auto ScreenLocation{FVector2D((ViewPortSizeX * CrossHairXLocation),(ViewPortSizeY * CrossHairYLocation))};

	// deproject corsshair into world direction
	FVector LookDirection;
	if(GetLookDirection(ScreenLocation, LookDirection))
	{

		return GetLookVectorHitLocation(LookDirection, HitLocation);
	}

	return false;
}


bool ATankPlayerController::GetLookVectorHitLocation(FVector Lookdirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation{PlayerCameraManager->GetCameraLocation()};
	auto EndLocation{StartLocation + (Lookdirection * LineTraceRange)};
	if(GetWorld()->LineTraceSingleByChannel(
			HitResult,
			StartLocation,
			EndLocation,
			ECollisionChannel::ECC_Camera)
		)
		{
			HitLocation = HitResult.Location;
			return true;
		}
		
	HitLocation = FVector(0);
	return false; //line trace failed
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{

	FVector CameraWorldLocation; //to be discarded
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);
	
}