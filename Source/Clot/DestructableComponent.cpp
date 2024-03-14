// Fill out your copyright notice in the Description page of Project Settings.


#include "DestructableComponent.h"
#include "Unit.h"

// Sets default values for this component's properties
UDestructableComponent::UDestructableComponent()
{
	// ...
}


// Called when the game starts
void UDestructableComponent::BeginPlay()
{
	Super::BeginPlay();

	if (UPrimitiveComponent* PrimitiveComponent = GetOwner()->GetComponentByClass<UPrimitiveComponent>())
	{
		PrimitiveComponent->OnComponentHit.AddDynamic(this, &UDestructableComponent::OnHit);
	}
}

void UDestructableComponent::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	float Momentum = 0.0f;
	float Magnitude = 0.0f;
	float Mass = 0.0f;

	if (UPrimitiveComponent* PrimitiveComponent = GetOwner()->GetComponentByClass<UPrimitiveComponent>())
	{
		Magnitude = GetOwner()->GetVelocity().Size();
		Mass = PrimitiveComponent->GetMass();

		Momentum = Mass * Magnitude;
	}

	if (Magnitude < 500)
	{
		return;
	}

	// TODO: Prevent multi hit via i frames
	if (UUnit* Unit = OtherActor->GetComponentByClass<UUnit>())
	{
		Unit->TakeDamage(Mass, DamageType::Blunt);
	}
}
