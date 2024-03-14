// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TP_MolotovComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CLOT_API UTP_MolotovComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTP_MolotovComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	/** Fire class to spawn */
	UPROPERTY(EditDefaultsOnly, Category="Molotov")
	TSubclassOf<class AActor> ExplosionClass;

	/** Fire class to spawn */
	UPROPERTY(EditDefaultsOnly, Category="Molotov")
	TSubclassOf<class AActor> FireClass;

	UPROPERTY(EditAnywhere, Category="Molotov")
	float ExplosionRadius;

	UFUNCTION(BlueprintCallable, Category="Molotov")
	void Explode();
};
