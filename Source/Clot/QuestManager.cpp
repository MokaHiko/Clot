// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestManager.h"

#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

#include "Quest.h"
#include "Unit.h"

// Sets default values
AQuestManager::AQuestManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AQuestManager::BeginPlay()
{
	Super::BeginPlay();

	// TODO: Check and serialize save file	

	// Create quests
	if (ACharacter* MyCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	{
		if (UUnit* Unit = MyCharacter->GetComponentByClass<UUnit>())
		{
			for(AQuest* Quest : Quests)
			{
				if(!Quest)
				{
					continue;
				}
				Quest->Activate(Unit);
			}
		}
	}
	// 	{
	// 		UWorld* const World = GetWorld();
	// 		if (World != nullptr)
	// 		{
	// 			const FRotator SpawnRotation = GetOwner()->GetActorRotation();
	// 			const FVector SpawnLocation = GetOwner()->GetActorLocation();

	// 			FActorSpawnParameters ActorSpawnParams;

	// 			// Allocate abilities array
	// 			Quests.Reserve(QuestTemplates.Num());

	// 			for (int i = 0; i < QuestTemplates.Num(); i++)
	// 			{
	// 				AActor* QuestActor = World->SpawnActor<AActor>(QuestTemplates[i], SpawnLocation, SpawnRotation, ActorSpawnParams);
	// 				FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);

	// 				if (!QuestActor->AttachToActor(GetOwner(), AttachmentRules))
	// 				{
	// 					UE_LOG(LogTemp, Display, TEXT("Failed to attach %s"), *QuestActor->GetName());
	// 				}

	// 				// Keep reference to Quest 
	// 				if (AQuest* Quest = Cast<AQuest>(QuestActor))
	// 				{
	// 					Quests.Add(Quest);
	// 				}
	// 			}
	// 		}
	// 	}
	// }

}

void AQuestManager::SerializeToJson(const char* Path)
{
}

// Called every frame
void AQuestManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Update quests
	if (ACharacter* MyCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	{
		if (UUnit* Unit = MyCharacter->GetComponentByClass<UUnit>())
		{
			for (AQuest* Quest : Quests)
			{
				if (!Quest)
				{
					continue;
					UE_LOG(LogTemp, Error, TEXT("Invalid Quest"));
				}

				if (!Quest->IsActive())
				{
					continue;
				}

				Quest->Update(Unit);
			}
		}
	}
}

