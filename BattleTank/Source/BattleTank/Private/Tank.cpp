// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
#include "Components/SceneComponent.h"
#include "Projectile.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankMovementComponent.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//no need to prtotect pointers as added at construction
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
	//TankMovementComponent = CreateDefaultSubobject<UTankMovementComponent>(FName("Movement Component"));
}

void ATank::SetBarrelReference(UTankBarrel* BarrelToSet) 
{
	TankAimingComponent->SetBarrelReference(BarrelToSet);
	LocalBarrel = BarrelToSet; //local barrel for spawning projectiles
}

void ATank::SetTurretReference(UTankTurret* TurretToSet) 
{
	TankAimingComponent->SetTurretReference(TurretToSet);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::AimAt(FVector HitLocation) 
{
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::FireProjectile() 
{
	bool isReloaded{(FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds};

	if(LocalBarrel && isReloaded)
	{
		auto Projectile{GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, 
														LocalBarrel->GetSocketLocation(FName("ProjectileLaunch")),
														LocalBarrel->GetSocketRotation(FName("ProjectileLaunch")))};
	
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds(); //reset to platform time to enable next fire
	}

}
