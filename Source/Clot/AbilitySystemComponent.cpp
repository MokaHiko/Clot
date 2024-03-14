// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystemComponent.h"
#include "Unit.h"

void UAbilitySystemComponent::ActivateAbility(int index)
{
	if(index > Abilities.Num())
	{
		UE_LOG(LogTemp, Error, TEXT("AbilitySystem has no ability at index %d"), index);
		return;
	}

	if (UUnit* Unit = GetOwner()->GetComponentByClass<UUnit>())
	{
		if (Abilities[index]->CanActivate())
		{
			Abilities[index]->Activate(Unit);
		}
	}
}

// Sets default values for this component's properties
UAbilitySystemComponent::UAbilitySystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UAbilitySystemComponent::BeginPlay()
{
	Super::BeginPlay();

	// Instantiate and attach abilities to player
	if (UUnit* Unit = GetOwner()->GetComponentByClass<UUnit>())
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			const FRotator SpawnRotation = GetOwner()->GetActorRotation();
			const FVector SpawnLocation = GetOwner()->GetActorLocation();

			FActorSpawnParameters ActorSpawnParams;

			// Allocate abilities array
			Abilities.Reserve(AbilityTemplates.Num());

			for (int i = 0; i < AbilityTemplates.Num(); i++)
			{
				AActor* AbilityActor = World->SpawnActor<AActor>(AbilityTemplates[i], SpawnLocation, SpawnRotation, ActorSpawnParams);
				FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);

				if(!AbilityActor->AttachToActor(GetOwner(), AttachmentRules))
				{
					UE_LOG(LogTemp, Display, TEXT("Failed to attach %s"), *AbilityActor->GetName());
				}

				// Keep reference to Ability 
				if (AAbility* Ability = Cast<AAbility>(AbilityActor))
				{
					Abilities.Add(Ability);
				}
			}
		}
	}
}


// Called every frame
void UAbilitySystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (UUnit* Unit = GetOwner()->GetComponentByClass<UUnit>())
	{
		for(AAbility* Ability : Abilities)
		{
			if(Ability->IsActive())
			{
				Ability->Update(Unit, DeltaTime);
			}
			else
			{
				Ability->ReduceCooldown(DeltaTime);
			}
		}
	}
}

