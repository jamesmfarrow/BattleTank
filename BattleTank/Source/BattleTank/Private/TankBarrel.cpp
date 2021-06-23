// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed) 
{

	// move the barrel right amount this frame
	// given max speed and frame time
	auto ElevationChange{FMath::Clamp<float>(RelativeSpeed, -1.f, +1.f) * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds};
	auto RawNewElevation{GetRelativeRotation().Pitch + ElevationChange};

	SetRelativeRotation(FRotator(FMath::Clamp<float>(RawNewElevation, MinElevationDegrees, MaxElevationDegrees), 0.f, 0.f));
}