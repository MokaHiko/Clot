// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability.h"

// Sets default values
AAbility::AAbility()
{
}

// Called when the game starts or when spawned
void AAbility::BeginPlay()
{
	Super::BeginPlay();

	ActiveTime = 0.0f;
	CooldownTime = Cooldown;
}

void AAbility::Tick(float DeltaTime) {}

void AAbility::ReduceCooldown(float DeltaTime) 
{
	CooldownTime += DeltaTime;
}
