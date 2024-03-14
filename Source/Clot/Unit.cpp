// Fill out your copyright notice in the Description page of Project Settings.

#include "Unit.h"

#include "GameFramework/Actor.h"
#include "TimerManager.h"

#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values for this component's properties
UUnit::UUnit()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UUnit::TakeDamage(float damage, DamageType type)
{
	Health -= damage;

	// Invoke on damage event
	OnTakeDamage.Broadcast(this, damage);

	if (Health <= 0)
	{
		ApplyStatus(StatusEffect::Dead);
		return;
	}

	if (type == DamageType::Pure)
	{
		return;
	}

	if (type == DamageType::Blunt)
	{
		// if (USkeletalMeshComponent* Mesh = GetOwner()->GetComponentByClass<USkeletalMeshComponent>())
		// {
		// 	Mesh->SetSimulatePhysics(true);
		// 	UE_LOG(LogTemp, Display, TEXT("Mesh Enabled"));
		// }

		// if (UCapsuleComponent* Mesh = GetOwner()->GetComponentByClass<UCapsuleComponent>())
		// {
		// 	Mesh->SetSimulatePhysics(true);
		// 	UE_LOG(LogTemp, Display, TEXT("Capsule Enabled"));
		// }

		// TODO: Get up
		// if(RigidBodyResetHandle.IsValid())
		// {
		// 	RigidBodyResetHandle.Invalidate();
		// }

		// float KnockDownRecoveryTime = 2.0f;
		// GetOwner()->GetWorldTimerManager().SetTimer(RigidBodyResetHandle, this, &UUnit::ResetRagdoll, KnockDownRecoveryTime);
	}
}

void UUnit::ApplyStatus(StatusEffect status)
{
	switch (status)
	{
	case(StatusEffect::Burning):
	{
		if (IsStatusEffect(StatusEffect::Burning))
		{
			UE_LOG(LogTemp, Display, TEXT("Already burning. Will Extend!"));
			return;
		}

		if (FireEffect != nullptr)
		{
			UWorld* const World = GetWorld();
			if (World != nullptr)
			{
				const FRotator SpawnRotation = GetOwner()->GetActorRotation();
				const FVector SpawnLocation = GetOwner()->GetActorLocation();

				//Set Spawn Collision Handling Override
				FActorSpawnParameters ActorSpawnParams;
				// ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

				// Spawn the projectile at the muzzle
				AActor* Fire = World->SpawnActor<AActor>(FireEffect, SpawnLocation, SpawnRotation, ActorSpawnParams);

				FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
				Fire->AttachToActor(GetOwner(), AttachmentRules);
			}
		}
	}break;
	case(StatusEffect::Dead):
	{
		// Check if already queud for death
		if (!IsStatusEffect(StatusEffect::Dead))
		{
			Die();
		}
	}break;
	default:
	{
		UE_LOG(LogTemp, Warning, TEXT("Attemping to apply uknown status effect!"));
	}break;
	}

	Status |= status;
}

void UUnit::RemoveStatus(StatusEffect status)
{
	Status &= ~status;
}

void UUnit::Die()
{
	if (USkeletalMeshComponent* Mesh = GetOwner()->GetComponentByClass<USkeletalMeshComponent>())
	{
		Mesh->SetSimulatePhysics(true);
	}

	GetOwner()->SetLifeSpan(3.0f);
}

// Called when the game starts
void UUnit::BeginPlay()
{
	Super::BeginPlay();

	// Reset
	Health = BaseStats.MaxHealth;
	Status = StatusEffect::Clean;
}

// Called every frame
void UUnit::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (IsStatusEffect(StatusEffect::Dead))
	{
		return;
	}

	if (IsStatusEffect(StatusEffect::Burning))
	{
		TakeDamage(50 * DeltaTime);
	}
}

void UUnit::ResetRagdoll()
{
	if (USkeletalMeshComponent* Mesh = GetOwner()->GetComponentByClass<USkeletalMeshComponent>())
	{
		Mesh->SetSimulatePhysics(false);
	}

	RigidBodyResetHandle.Invalidate();
}

bool UUnit::IsStatusEffect(StatusEffect effect) const
{
	return (Status & effect) == effect;
}
