// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability.h"
#include "DashAbility.generated.h"

/**
 * 
 */
UCLASS()
class CLOT_API ADashAbility : public AAbility
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, Category="Dash")
	int32 Instances = 2;

	UPROPERTY(EditDefaultsOnly, Category="Dash")
	float DashMultiplier = 3.0f;

	virtual void OnActivate(UUnit* Unit) override;
};
