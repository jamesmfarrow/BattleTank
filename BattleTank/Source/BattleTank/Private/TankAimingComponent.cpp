// Fill out your copyright notice in the Description page of Project Settings.


#include "Kismet/GameplayStatics.h"
#include "TankAimingComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent* BarrelToSet) 
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed) 
{
	if(!Barrel) return;

	FVector OutLanchVelocity;
	FVector StartLocation{Barrel->GetSocketLocation(FName("ProjectileLaunch"))};

	//calculate the OutLanchVelocity
	bool bHaveAimSolution{UGameplayStatics::SuggestProjectileVelocity(this, OutLanchVelocity, StartLocation,
			                  			HitLocation, LaunchSpeed, ESuggestProjVelocityTraceOption::DoNotTrace)};

	if(bHaveAimSolution)
	{
		auto AimDirection{OutLanchVelocity.GetSafeNormal()};
		MoveBarrelTowards(AimDirection);
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) 
{
	//work out difference between current barrel position/rotation and AimDirection
	auto BarrelRotator{Barrel->GetForwardVector().Rotation()};
	auto AimAsRotation{AimDirection.Rotation()};
	UE_LOG(LogTemp, Warning, TEXT("AimAsRotator: %s"), *AimAsRotation.ToString());
	// move th ebarrel right amount this frame
	//given max speed and frame time
}