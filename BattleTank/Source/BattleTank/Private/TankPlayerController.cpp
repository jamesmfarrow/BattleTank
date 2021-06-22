// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay() 
{
	Super::BeginPlay();
	
	ATank* MyTank{GetControlledTank()};
	/*if(MyTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank is possessed: %s"), *(MyTank->GetName()));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No possessed tank"));
	}*/
}

void ATankPlayerController::Tick(float DeltaTime) 
{

	Super::Tick(DeltaTime);
	AimAtCrossHairs();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimAtCrossHairs() 
{
	if(!GetControlledTank()) return;

	FVector HitLocation; //out parameter
	if(GetSightHitRayLocation(HitLocation))
	{
		GetControlledTank()->AimAt(HitLocation);
	}

}

// get world location of linetrace through crosshair, true if it hits landscape
bool ATankPlayerController::GetSightHitRayLocation(FVector& OutHitLocation) const
{
	//find cross hair position in pixel co-ordinates
	int32 ViewPortSizeX, ViewPortSizeY;
	GetViewportSize(ViewPortSizeX, ViewPortSizeY); 
	auto ScreenLocation{FVector2D((ViewPortSizeX * CrossHairXLocation),(ViewPortSizeY * CrossHairYLocation))};

	// deproject corsshair into world direction
	FVector OutLookDirection;
	if(GetLookDirection(ScreenLocation, OutLookDirection))
	{
		//TODO
		// line trace along that LookDirection, and see what we hit(up to a max range)
		GetLookVectorHitLocation(OutLookDirection, OutHitLocation);
	}

	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{

	FVector CameraWorldLocation; //to be discarded
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);
	
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
			ECollisionChannel::ECC_Visibility)
		)
		{
			HitLocation = HitResult.Location;
			return true;
		}
	
	HitLocation = FVector(0.f, 0.f, 0.f);
	return false; //line trace failed
}