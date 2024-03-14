// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ability.generated.h"

class UUnit;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CLOT_API AAbility : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAbility();

protected:
	// Final override life time functions
	virtual void BeginPlay() final override;
	virtual void Tick(float DeltaTime) final override;
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Ability")
	float StartupTime;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Ability")
	float Duration;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Ability")
	float Cooldown = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Ability")
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Ability")
	float Range;

	/** If true then more than once instance of the ability can activate at the same time*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Ability")
	bool Stackable = false;

	/**Returns whether ability can activate */
	const bool CanActivate() const {return (!IsActive() || Stackable) && (CooldownTime > Cooldown);}

	void Activate(UUnit* Unit)
	{
		//TODO: Global Timer for activation time
		OnActivate(Unit);
		CooldownTime = 0.0f;
		Active = true;
	}

	void Update(UUnit* Unit, float DeltaTime)
	{
		OnUpdate(Unit, DeltaTime);
		ActiveTime += DeltaTime;

		if(ActiveTime >= Duration)
		{
			Deactivate(Unit);
		}
	}

	void ReduceCooldown(float DeltaTime);

	void Deactivate(UUnit* Unit)
	{
		OnDeactivate(Unit);

		Active = false;
		ActiveTime = 0.0f;
	}

	inline const bool IsActive() const {return Active;}

	/* Time active */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Ability")
	float ActiveTime;

	/* Time inactive */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Ability")
	float CooldownTime;

	/* Is active */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Ability")
	bool Active;
protected:
	virtual void OnActivate(UUnit* Unit) {};
	virtual void OnUpdate(UUnit* Unit, float DeltaTime) {};
	virtual void OnDeactivate(UUnit* Unit) {};
private:
};
