// Copyright (C) Rapyuta Robotics


#include "TurtlebotMovementComponent.h"

#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"

void UTurtlebotMovementComponent::UpdateMovement(float DeltaTime)
{
	const FQuat OldRotation = UpdatedComponent->GetComponentQuat();

	FVector position = UpdatedComponent->ComponentVelocity * DeltaTime;
	FQuat DeltaRotation(FVector(0.0f, 0.0f, 1.0f), -AngularVelocity.Z * DeltaTime);

	DesiredRotation = OldRotation * DeltaRotation;
	DesiredMovement = (OldRotation * position);
}

void UTurtlebotMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	if (!ShouldSkipUpdate(DeltaTime))
	{
		Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

		// Make sure that everything is still valid, and that we are allowed to move.
		if (IsValid(UpdatedComponent))
		{
			UpdateMovement(DeltaTime);

			FHitResult Hit;
			SafeMoveUpdatedComponent(DesiredMovement, DesiredRotation, true, Hit);

			// If we bumped into something, try to slide along it
			if (Hit.IsValidBlockingHit())
			{
				SlideAlongSurface(DesiredMovement, 1.0f - Hit.Time, Hit.Normal, Hit);
			}
		}

		UpdateComponentVelocity();
		AngularVelocity = FVector::ZeroVector;
		Velocity = FVector::ZeroVector;
	}
}
