// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Enum for aiming state
UENUM()
enum class EFiringState : uint8
{
	Locked,
	Aiming,
	Reloading
};

//forward declaration
class UTankBarrel;
class UTankTurret;

// Holds the barrel's properties and elavate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	void AimAt(FVector HitLocation);	

private:
	// Sets default values for this component's properties, constructor
	UTankAimingComponent();

	UTankBarrel* Barrel{nullptr};
	UTankTurret* Turret{nullptr};

	void MoveBarrelTowards(FVector AimDirection);

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed{4000.f};


protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState{EFiringState::Reloading};
};








