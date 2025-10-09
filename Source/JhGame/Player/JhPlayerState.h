// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "JhPlayerState.generated.h"

class UJhPawnData;
class UJhExperienceDefinition;
/**
 * 
 */
UCLASS()
class JHGAME_API AJhPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	/**
	* AActor's interface
	*/
	virtual void PostInitializeComponents() final;

	/**
	 * member methods
	 */
	void OnExperienceLoaded(const UJhExperienceDefinition* CurrentExperience);

	UPROPERTY()
	TObjectPtr<const UJhPawnData> PawnData;
};
