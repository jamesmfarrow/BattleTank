// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	

	// Called by the engine when actor damage is dealt
 	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

	//returns current health as %age between 0 & 1
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetPercentHealth() const;

	FTankDelegate OnDeath;

private:
	// Sets default values for this pawn's properties
	ATank();

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
 	int32 StartingHealth = 100;

 	UPROPERTY(VisibleAnywhere, Category = "Health")
 	int32 CurrentHealth = StartingHealth;

};







