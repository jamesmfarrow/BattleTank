// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "Math/Vector2D.h"
#include "UObject/ObjectMacros.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

//forward declaration
class ATank;

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()


private:
	ATank* GetControlledTank() const;
	
	UPROPERTY(EditAnywhere)
	float CrossHairXLocation{0.5f};
	UPROPERTY(EditAnywhere)
	float CrossHairYLocation{0.33333f};

	UPROPERTY(EditAnywhere)
	float LineTraceRange{1000000.f}; //10km

	//start the tank moving the barrel so that the shot would hit
	//where the corsshiat intersects th eowrld
	void AimAtCrossHairs();

	// return an OUT parameter, true if it hits landscape
	bool GetSightHitRayLocation(FVector& OutHitLocation) const;

	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

	bool GetLookVectorHitLocation(FVector Lookdirection, FVector& HitLocation) const;

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};
















