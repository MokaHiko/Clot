// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TP_WeaponComponent.h"
#include "TP_GravityGunComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNewTarget, float, Distance);

UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CLOT_API UTP_GravityGunComponent : public UTP_WeaponComponent
{
	GENERATED_BODY()
public:
	/** Delegate to whom anyone can subscribe to receive this event */
	UPROPERTY(BlueprintAssignable, Category = "GravityGun")
	FNewTarget OnNewTarget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="GravityGun")
	float PickUpRadius = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="GravityGun")
	float SweepSphereRadius = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="GravityGun")
	float HoldDistance = 200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="GravityGun")
	float AltFireForceMagnitude = 1000000.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Gravity Gun")
	bool IsHolding = false;
public:
	UTP_GravityGunComponent();

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
public:
	virtual void Fire() override;
	virtual void AltFire() override;

	virtual void OnAttach() override;
	virtual void OnDetach() override;
private:
	AActor* CurrentGrabbable = nullptr;

	void Release();
	void Hold();
};
