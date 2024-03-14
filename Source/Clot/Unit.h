// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Unit.generated.h"

class UUnit;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FTakeDamage, UUnit*, Unit, float, Damage);

enum class DamageType
{
	Pure,
	Blunt,
};

UENUM(BlueprintType)
enum class StatusEffect 
{
	Clean = 0,
	Dead = 1,
	Bleeding = 1 << 1,
	Burning = 1 << 2
};

inline StatusEffect operator~ (StatusEffect a) { return (StatusEffect)~(int)a; }
inline StatusEffect operator| (StatusEffect a, StatusEffect b) { return (StatusEffect)((int)a | (int)b); }
inline StatusEffect operator& (StatusEffect a, StatusEffect b) { return (StatusEffect)((int)a & (int)b); }
inline StatusEffect operator^ (StatusEffect a, StatusEffect b) { return (StatusEffect)((int)a ^ (int)b); }
inline StatusEffect& operator|= (StatusEffect& a, StatusEffect b) { return (StatusEffect&)((int&)a |= (int)b); }
inline StatusEffect& operator&= (StatusEffect& a, StatusEffect b) { return (StatusEffect&)((int&)a &= (int)b); }
inline StatusEffect& operator^= (StatusEffect& a, StatusEffect b) { return (StatusEffect&)((int&)a ^= (int)b); }

USTRUCT(BlueprintType)
struct FUnitStats
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxHealth = 1000.0f;
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CLOT_API UUnit : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "Unit")
	FTakeDamage OnTakeDamage;

	// Sets default values for this component's properties
	UUnit();

	void TakeDamage(float damage, DamageType type = DamageType::Pure);

	void ApplyStatus(StatusEffect status);
	void RemoveStatus(StatusEffect status);
public:
	virtual void Die();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FUnitStats BaseStats;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	StatusEffect Status;

	/** Fire effect class*/
	UPROPERTY(EditDefaultsOnly, Category=StatusEffects)
	TSubclassOf<class AActor> FireEffect;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
private:
	void ResetRagdoll();

	// Returns whether or not the unit is effected by status;
	bool IsStatusEffect(StatusEffect effect) const;

	FTimerHandle RigidBodyResetHandle;
};
