// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"


//forward declaration
class UTankBarrel;
class AProjectile;


UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

private:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;

	// variable projectile luanch speed
	UPROPERTY(EditDefaultsOnly, Category = Firing) // TO DO remove one firing is moved to aiming component
	float LaunchSpeed{4000.f};

	//local barrel reference for spawning projectile
	UTankBarrel* LocalBarrel{nullptr}; // TO DO remove

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeInSeconds{3.f};

	double LastFireTime{0};
	

public:

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void FireProjectile();

};






