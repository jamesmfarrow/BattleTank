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
class AProjectile;

// Holds the barrel's properties and elavate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void FireProjectile();


protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState{EFiringState::Reloading};

private:
	// Sets default values for this component's properties, constructor
	UTankAimingComponent();

	virtual void BeginPlay() override;
	
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	void MoveBarrelTowards(FVector AimDirection);

	UTankBarrel* Barrel{nullptr};
	UTankTurret* Turret{nullptr};

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;

	// variable projectile luanch speed
	UPROPERTY(EditDefaultsOnly, Category = Firing) // TO DO remove one firing is moved to aiming component
	float LaunchSpeed{4000.f};

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeInSeconds{3.f};

	double LastFireTime{0};


};








