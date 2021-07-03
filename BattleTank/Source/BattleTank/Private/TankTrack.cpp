// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"

UTankTrack::UTankTrack() 
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) 
{
    // recipe for sideways forces/friction
    //1 calculate the slippage speed (dot product)
    auto SlippageSpeed{FVector::DotProduct(GetRightVector(), GetComponentVelocity())};
    //2 work out the required acceln this frame to correct, - to apply in opposite direction and correct slippage
    auto CorrectionAcceleration{-SlippageSpeed / DeltaTime * GetRightVector()};
    // 3 calculate and aply sideways force ( F = ma)
    auto TankRoot{Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent())};
    auto CorrectionForce{(TankRoot->GetMass() * CorrectionAcceleration) / 2}; // because there are 2 tracks
    TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::SetThrottle(float Throttle) 
{   
    //TO DO clamp throttle value so player cann not over-drive
    //forwardvector of track, 1 max force, 0 no force, -1 max reverse force
    auto ForceApplied{GetForwardVector() * Throttle * MaxTrackDrivingForce};

    //get the track location
    auto ForceLocation{GetComponentLocation()};

    // get the tank component and apply the force at the location
    auto TankRoot{Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent())};
    TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}
