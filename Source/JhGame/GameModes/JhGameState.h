// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "JhGameState.generated.h"

class UJhExperienceManagerComponent;
/**
 * 
 */
UCLASS()
class JHGAME_API AJhGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	AJhGameState();

public:
	UPROPERTY();
	TObjectPtr<UJhExperienceManagerComponent> ExperienceManagerComponent;
};
