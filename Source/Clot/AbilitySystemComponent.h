// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Ability.h"
#include "AbilitySystemComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CLOT_API UAbilitySystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPROPERTY(EditAnywhere, Category="Abilities");
	TArray<TSubclassOf<class AAbility>> AbilityTemplates;

	void ActivateAbility(int index);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Abilities");
	TArray<AAbility*> Abilities;

	// Sets default values for this component's properties
	UAbilitySystemComponent();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
