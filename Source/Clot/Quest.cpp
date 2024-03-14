// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest.h"

#include "Unit.h"
#include "Engine/World.h"
#include "Components/SphereComponent.h"

// Sets default values
AQuest::AQuest()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

const bool AQuest::IsComplete() const
{
	return QuestObjectives == QuestType::Complete;
}

void AQuest::Update(UUnit* Unit)
{
}

void AQuest::Activate(UUnit* Unit)
{
	Player = Unit;

	UWorld* const World = GetWorld();
	if (World == nullptr || Target == nullptr)
	{
		return;
	}

	if (IsQuestType(QuestType::GoTo))
	{
		if (QuestSphereTemplate != nullptr)
		{
			const FRotator SpawnRotation = Target->GetActorRotation();
			const FVector SpawnLocation = Target->GetActorLocation();

			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;

			// Register to callback 
			AActor* QuestSphere = World->SpawnActor<AActor>(QuestSphereTemplate, SpawnLocation, SpawnRotation, ActorSpawnParams);
			if (USphereComponent* SphereCollider = QuestSphere->GetComponentByClass<USphereComponent>())
			{
				SphereCollider->OnComponentBeginOverlap.AddDynamic(this, &AQuest::OnQuestSphereBeginOverlap);
			}

			QuestObjectives |= QuestType::GoTo;
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Invalid QuestSphereTemplate!"));
		}
	}
}

// Called when the game starts or when spawned
void AQuest::BeginPlay()
{
	Super::BeginPlay();
}

void AQuest::OnQuestSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!Target)
	{
		UE_LOG(LogTemp, Warning, TEXT("Go to quest has no target"));
		return;
	}

	if (Player != nullptr && Player->GetOwner() == OtherActor)
	{
		CompleteObjective(QuestType::GoTo);
		UE_LOG(LogTemp, Display, TEXT("Finished GOTO"));
	}
}

// Called every frame
void AQuest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


bool AQuest::IsQuestType(QuestType eType) const
{
	return (Type & eType) == eType;
}

void AQuest::CompleteObjective(QuestType Objective)
{
	QuestObjectives &= ~Objective;
}
