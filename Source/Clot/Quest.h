// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Quest.generated.h"

UENUM(BlueprintType)
enum class QuestType
{
	Complete = 0,
	GoTo = 1,
	KillX = 1 << 1,
	Collect = 1 << 2,
};

inline QuestType operator~ (QuestType a) { return (QuestType)~(int)a; }
inline QuestType operator| (QuestType a, QuestType b) { return (QuestType)((int)a | (int)b); }
inline QuestType operator& (QuestType a, QuestType b) { return (QuestType)((int)a & (int)b); }
inline QuestType operator^ (QuestType a, QuestType b) { return (QuestType)((int)a ^ (int)b); }
inline QuestType& operator|= (QuestType& a, QuestType b) { return (QuestType&)((int&)a |= (int)b); }
inline QuestType& operator&= (QuestType& a, QuestType b) { return (QuestType&)((int&)a &= (int)b); }
inline QuestType& operator^= (QuestType& a, QuestType b) { return (QuestType&)((int&)a ^= (int)b); }

class UUnit;

UCLASS()
class CLOT_API AQuest : public AActor
{
	GENERATED_BODY()
	
	public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Quest");
	FString Name = "";

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Quest");
	FString Description = "";

	UPROPERTY(EditAnywhere, Category="Quest")
	QuestType Type;
public:	
	// Sets default values for this actor's properties
	AQuest();

	UFUNCTION(BlueprintCallable, Category="Quest")
	const bool IsComplete() const;

	UFUNCTION()
	virtual void Update(UUnit* Unit);

	/** Toggles whether not the quest is active*/
	UFUNCTION()
	void Activate(UUnit* Unit); 

	/** Returns whether not the quest is active*/
	UFUNCTION()
	inline bool IsActive() const {return Active;}
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Quest|GoTo");
	TSubclassOf<class AActor> QuestSphereTemplate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Quest|GoTo");
	AActor* Target;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Quest|GoTo");
	float DetectRadius = 32.0f;

	UFUNCTION()
	void OnQuestSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool IsQuestType(QuestType eType) const;
private:
	void CompleteObjective(QuestType Objective);
	
	UUnit* Player;
	QuestType QuestObjectives;
	bool Active = false;
};
