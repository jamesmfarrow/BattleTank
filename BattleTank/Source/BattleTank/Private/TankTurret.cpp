// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed) 
{

	// move the barrel right amount this frame
	// given max speed and frame time
	auto RotationChange{FMath::Clamp<float>(RelativeSpeed, -1.f, +1.f) * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds};
	auto NewRotation{GetRelativeRotation().Yaw + RotationChange};

	SetRelativeRotation(FRotator(0.f, NewRotation, 0.f));
}