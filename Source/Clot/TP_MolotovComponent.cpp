// Fill out your copyright notice in the Description page of Project Settings.


#include "TP_MolotovComponent.h"

// Sets default values for this component's properties
UTP_MolotovComponent::UTP_MolotovComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.

	// ...
}


// Called when the game starts
void UTP_MolotovComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}

void UTP_MolotovComponent::Explode()
{
	UWorld* const World = GetWorld();
	if (World != nullptr)
	{
		const FRotator SpawnRotation = GetOwner()->GetActorRotation();
		const FVector SpawnLocation = GetOwner()->GetActorLocation();

		//Set Spawn Collision Handling Override
		FActorSpawnParameters ActorSpawnParams;

		// Spawn explosion effect 
		if (ExplosionClass != nullptr)
		{
			AActor* Explosion = World->SpawnActor<AActor>(ExplosionClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
		}
		// Spawn the projectile 
		if (FireClass != nullptr)
		{
			AActor* Fire = World->SpawnActor<AActor>(FireClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
		}
	}

	GetOwner()->Destroy();
}

