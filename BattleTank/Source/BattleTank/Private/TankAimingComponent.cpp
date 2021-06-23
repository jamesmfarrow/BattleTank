// Fill out your copyright notice in the Description page of Project Settings.


#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankAimingComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true; // TO DO should this tick

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet) 
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet) 
{
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed) 
{
	if(!Barrel) return;
	if(Turret) UE_LOG(LogTemp, Warning, TEXT("We have a Turret!!!")); 

	FVector OutLaunchVelocity;
	FVector StartLocation{Barrel->GetSocketLocation(FName("ProjectileLaunch"))};

	//calculate the OutLanchVelocity
	bool bHaveAimSolution{UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation, HitLocation, LaunchSpeed, false, 0.f, 0.f,
																		 ESuggestProjVelocityTraceOption::DoNotTrace, FCollisionResponseParams::DefaultResponseParam, TArray<AActor*>(), false)};


	if(bHaveAimSolution)
	{
		auto AimDirection{OutLaunchVelocity.GetSafeNormal()};
		MoveBarrelTowards(AimDirection);
		//UE_LOG(LogTemp, Warning, TEXT("Aim Solution found")); 
	}
	else
	{
		//UE_LOG(LogTemp, Error, TEXT("No Aim Solution found"));
		//UE_LOG(LogTemp, Error, TEXT("No solution")); 
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) 
{
	//work out difference between current barrel position/rotation and AimDirection
	auto BarrelRotator{Barrel->GetForwardVector().Rotation()};
	auto AimAsRotation{AimDirection.Rotation()};
	auto DeltaRotator{AimAsRotation - BarrelRotator};
	
	Barrel->Elevate(DeltaRotator.Pitch); 
}
