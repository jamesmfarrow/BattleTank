// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet) 
{
    LeftTrack = LeftTrackToSet;
    RightTrack = RightTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) 
{
    //No need to call Super as we are replacing functionality
    //vectors below are required for dot product - IntendMOveForward()
    //and cross product IntendTurnRight()
    auto TankForward{GetOwner()->GetActorForwardVector().GetSafeNormal()}; //worldspace vector
    auto AIForwardIntention{MoveVelocity.GetSafeNormal()}; //worldspace vector


    auto ForwardThrow{FVector::DotProduct(TankForward, AIForwardIntention)};
    auto RotationThrow(FVector::CrossProduct(AIForwardIntention,TankForward).Z); // check the vectors are correct way round - it matters in cross product
    IntendMoveForward(ForwardThrow);
    IntendRotateClockwise(RotationThrow);
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
    auto Name{GetOwner()->GetName()};
    //UE_LOG(LogTemp, Warning, TEXT("%s is tyring to rotate : %f"),*Name, Throw)
    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(-Throw);
}
