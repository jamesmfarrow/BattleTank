// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"

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
