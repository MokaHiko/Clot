// Fill out your copyright notice in the Description page of Project Settings.


#include "TP_FireComponent.h"

#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"

#include "Unit.h"

// Sets default values for this component's properties
UTP_FireComponent::UTP_FireComponent()
{

}


// Called when the game starts
void UTP_FireComponent::BeginPlay()
{
	Super::BeginPlay();

	// Register our Overlap Event
	if (USphereComponent* SphereComponent = GetOwner()->GetComponentByClass<USphereComponent>())
	{
		SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &UTP_FireComponent::OnSphereBeginOverlap);
	}

	FTimerHandle LifeTimeHandle;
	GetOwner()->GetWorldTimerManager().SetTimer(LifeTimeHandle, this, &UTP_FireComponent::Die, Duration);
}

void UTP_FireComponent::Die() 
{
	GetOwner()->Destroy();
}

void UTP_FireComponent::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (UUnit* Unit = OtherActor->GetComponentByClass<UUnit>())
	{
		Unit->ApplyStatus(StatusEffect::Burning);
	}
}
