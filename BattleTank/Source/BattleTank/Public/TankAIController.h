// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"


UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()


private:
	
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void SetPawn(APawn* InPawn) override;

protected:
	//AI pathfinding to this radius of actor
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float AcceptanceRadius{8000.f}; // check if units are cm

	UFUNCTION()
	void OnPssessedTankDeath();
	
};








