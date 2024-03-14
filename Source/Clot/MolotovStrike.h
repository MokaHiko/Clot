// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability.h"
#include "MolotovStrike.generated.h"

/**
 * 
 */
UCLASS()
class CLOT_API AMolotovStrike : public AAbility
{
	GENERATED_BODY()

	/** Molotov class*/
	UPROPERTY(EditDefaultsOnly, Category=StatusEffects)
	TSubclassOf<class AActor> MolotovClass;

	/** Flare class*/
	UPROPERTY(EditDefaultsOnly, Category=StatusEffects)
	TSubclassOf<class AActor> FlareClass;
public:
	UPROPERTY(EditDefaultsOnly, Category="MolotovStrike")
	int32 MolotovCount = 2;

	UPROPERTY(EditDefaultsOnly, Category="MolotovStrike")
	float LaunchHeight = 5000;

	virtual void OnActivate(UUnit* Unit) override;
};
