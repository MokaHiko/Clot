// Fill out your copyright notice in the Description page of Project Settings.


#include "DashAbility.h"

#include "GameFramework/Character.h"
#include "Unit.h"

void ADashAbility::OnActivate(UUnit *Unit) 
{
	if(ACharacter* Character = Cast<ACharacter>(Unit->GetOwner()))
	{
		FVector Force = Character->GetVelocity();
		Force.Z = 0.0f;

		Force *= DashMultiplier;
		Character->LaunchCharacter(Force, false, false);
	}
}
