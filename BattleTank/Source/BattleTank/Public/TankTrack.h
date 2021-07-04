// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * Tank Track is used to set maximum driving force, and apply forces to move the tank
 */
UCLASS( meta=(BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	float CurrentThrottle{0.f};

	//mac force per track in newtons Force = mass * acceleration, 50 tonne tank 1g accel
	UPROPERTY(EditDefaultsOnly)
	float MaxTrackDrivingForce{500000};

	//sets a throttle between +1 and -1
	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float Throttle);

	
	//UFUNCTION(BlueprintCallable, Category = "Input")
	void DriveTrack();

private:
	//constructor
	UTankTrack();

	void ApplySidewaysForce();

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
};












