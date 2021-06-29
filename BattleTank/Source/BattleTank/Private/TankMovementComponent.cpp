// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "TankMovementComponent.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet) 
{
    LeftTrack = LeftTrackToSet;
    RightTrack = RightTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) 
{
    //No need to call Super as we are replacing functionality
	auto Name{GetOwner()->GetName()};
    UE_LOG(LogTemp, Warning, TEXT("%s is moving at %s"), *Name, *MoveVelocity.ToString())
}

void UTankMovementComponent::IntendMoveForward(float Throw) 
{
    if(!LeftTrack || !RightTrack) return;
    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendRotateClockwise(float Throw) 
{
    if(!LeftTrack || !RightTrack) return;
    //UE_LOG(LogTemp, Warning, TEXT("Rotate Clockwise: %f"), Throw)
    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(-Throw);
}
