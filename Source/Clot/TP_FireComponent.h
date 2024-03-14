// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TP_FireComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CLOT_API UTP_FireComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTP_FireComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void Die();
public:	
	UPROPERTY(EditAnywhere, Category="Fire")
	float EffectRadius = 45.0f;

	UPROPERTY(EditAnywhere, Category="Fire")
	float Duration = 5.0f;

	/** Code for when something overlaps this component */
	UFUNCTION()
	void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
