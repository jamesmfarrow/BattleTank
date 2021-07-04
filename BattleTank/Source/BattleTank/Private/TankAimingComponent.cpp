// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet) 
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
};

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) 
{
	if((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
	{
		FiringState = EFiringState::Reloading;
	}
	else if(IsBarrelMoving())
	{
		FiringState = EFiringState::Aiming;
	}
	else
	{
		FiringState = EFiringState::Locked;
	}
}

EFiringState UTankAimingComponent::GetFiringState() const
{
	return FiringState;
}

bool UTankAimingComponent::IsBarrelMoving() 
{
	if(!ensure(Barrel)) return false;
	auto BarrelForward{Barrel->GetForwardVector()};
	return !BarrelForward.Equals(AimDirection, 0.01); // FVectors are equal
}

void UTankAimingComponent::BeginPlay() 
{
	//so that first fire is after initial reload
	LastFireTime = FPlatformTime::Seconds(); //reset to platform time to enable next fire
}

void UTankAimingComponent::AimAt(FVector HitLocation) 
{
	if(!ensure(Barrel)) return;

	FVector OutLaunchVelocity;
	FVector StartLocation{Barrel->GetSocketLocation(FName("ProjectileLaunch"))};

	//calculate the OutLanchVelocity
	bool bHaveAimSolution{UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation, HitLocation, LaunchSpeed, false, 0.f, 0.f,
																		 ESuggestProjVelocityTraceOption::DoNotTrace, FCollisionResponseParams::DefaultResponseParam, TArray<AActor*>(), false)};


	if(bHaveAimSolution)
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDir) 
{
	if(!ensure(Barrel && Turret)) return;
	//work out difference between current barrel position/rotation and AimDirection
	auto BarrelRotator{Barrel->GetForwardVector().Rotation()};
	auto AimAsRotation{AimDir.Rotation()};
	auto DeltaRotator{AimAsRotation - BarrelRotator};
	
	Barrel->Elevate(DeltaRotator.Pitch);

	//Always yaw shortest route
	if(FMath::Abs(DeltaRotator.Yaw) <= 180)
	{
		Turret->Rotate(DeltaRotator.Yaw);
	}
	else
	{
		Turret->Rotate(-DeltaRotator.Yaw);
	}
}

void UTankAimingComponent::FireProjectile() 
{
	if(FiringState != EFiringState::Reloading)
	{
		if(!ensure(Barrel)) { return; }
		if(!ensure(ProjectileBlueprint)) { return; }
		auto Projectile{GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, 
														Barrel->GetSocketLocation(FName("ProjectileLaunch")),
														Barrel->GetSocketRotation(FName("ProjectileLaunch")))};
	
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}

}