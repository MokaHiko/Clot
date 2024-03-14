// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Quest.h"
#include "QuestManager.generated.h"

UCLASS()
class CLOT_API AQuestManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AQuestManager();

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<class AQuest>> QuestTemplates;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="QuestManager")
	TArray<AQuest*> Quests;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Serialize current quests progress as json
	void SerializeToJson(const char* Path);

	// Serialize current quests progress as json
	//void DeserializeJson(const char* Path);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
