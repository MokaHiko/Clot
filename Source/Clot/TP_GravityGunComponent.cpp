// Fill out your copyright notice in the Description page of Project Settings.

#include "TP_GravityGunComponent.h"

#include "ClotCharacter.h"
#include "DrawDebugHelpers.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

UTP_GravityGunComponent::UTP_GravityGunComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
}

void UTP_GravityGunComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!IsHolding || Character == nullptr || Character->GetController() == nullptr)
	{
		return;
	}

	if (UPhysicsHandleComponent* PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>())
	{
		APlayerController* PlayerController = Cast<APlayerController>(Character->GetController());
		const FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();

		const FVector SpawnLocation = GetOwner()->GetActorLocation() + SpawnRotation.RotateVector(MuzzleOffset);
		const FVector Direction = PlayerController->PlayerCameraManager->GetActorForwardVector();
		const FVector TargetLocation = SpawnLocation + (Direction * HoldDistance);

		PhysicsHandle->SetTargetLocation(TargetLocation);
	}
}

void UTP_GravityGunComponent::AltFire()
{
	if (Character == nullptr || Character->GetController() == nullptr)
	{
		return;
	}

	// Release
	if (IsHolding)
	{
		if (UPhysicsHandleComponent* PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>())
		{
			PhysicsHandle->ReleaseComponent();
			IsHolding = false;
		}

		return;
	}

	// Hold
	UWorld* const World = GetWorld();
	if (World == nullptr)
	{
		return;
	}

	APlayerController* PlayerController = Cast<APlayerController>(Character->GetController());
	const FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();

	// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
	const FVector SpawnLocation = GetOwner()->GetActorLocation() + SpawnRotation.RotateVector(MuzzleOffset);
	const FVector Direction = PlayerController->PlayerCameraManager->GetActorForwardVector();

	FHitResult OutHit = {};
	FCollisionShape CollisionSphere = FCollisionShape::MakeSphere(SweepSphereRadius);
	bool Res = World->SweepSingleByChannel(OutHit, SpawnLocation, SpawnLocation + (Direction * PickUpRadius), FQuat::Identity, ECC_GameTraceChannel2, CollisionSphere);

	// Check
	if (!Res || !OutHit.GetActor()->IsRootComponentMovable())	
	{
		return;
	}

	DrawDebugLine(World, SpawnLocation, OutHit.ImpactPoint, FColor::Red, false, 5.0f);
	DrawDebugSphere(World, OutHit.ImpactPoint, SweepSphereRadius, 10, FColor::Green, false, 5.0f);

	UPhysicsHandleComponent* PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	PhysicsHandle->GrabComponentAtLocationWithRotation(OutHit.GetComponent(), NAME_None, OutHit.ImpactPoint, GetOwner()->GetActorRotation());
	IsHolding = true;

	// Try and play the sound if specified
	// if (FireSound != nullptr)
	// {
	// 	UGameplayStatics::PlaySoundAtLocation(this, FireSound, Character->GetActorLocation());
	// }

	// Try and play a firing animation if specified
	if (FireAnimation != nullptr)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = Character->GetMesh1P()->GetAnimInstance();
		if (AnimInstance != nullptr)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}
}

void UTP_GravityGunComponent::Fire()
{
	if (!IsHolding || Character == nullptr || Character->GetController() == nullptr)
	{
		return;
	}

	if (UPhysicsHandleComponent* PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>())
	{
		if (TObjectPtr<UPrimitiveComponent> GrabbedComponent = PhysicsHandle->GrabbedComponent)
		{
			PhysicsHandle->ReleaseComponent();
			IsHolding = false;

			APlayerController* PlayerController = Cast<APlayerController>(Character->GetController());
			const FVector Direction = PlayerController->PlayerCameraManager->GetActorForwardVector();

			UE_LOG(LogTemp, Display, TEXT("%s"), *Direction.ToCompactString());
			GrabbedComponent->AddImpulse(Direction * AltFireForceMagnitude, NAME_None);
		}
	}
}
