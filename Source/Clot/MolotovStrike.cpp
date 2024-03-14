// Fill out your copyright notice in the Description page of Project Settings.


#include "MolotovStrike.h"

void AMolotovStrike::OnActivate(UUnit* Unit)
{
	if (MolotovClass != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			const FRotator SpawnRotation = GetActorRotation();
			FVector SpawnLocation = GetActorLocation();

			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;

			// Spawn Flare
			AActor* Flare = World->SpawnActor<AActor>(FlareClass, SpawnLocation + (GetActorForwardVector() * 20.0f), SpawnRotation, ActorSpawnParams);
			Flare->SetLifeSpan(5.0f);

			// Spawn the projectile at the muzzle
			SpawnLocation.Z += LaunchHeight;
			AActor* Molotov = World->SpawnActor<AActor>(MolotovClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
		}
	}
}
