// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "JhGameModeBase.generated.h"

class UJhExperienceDefinition;
class UJhPawnData;
/**
 * 
 */
UCLASS()
class JHGAME_API AJhGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AJhGameModeBase();

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	/* GameState 생성 완료 후 호출 */
	virtual void InitGameState() final; 

	/** GetDefaultPawnClassForController */
	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) final;

	/** HandleStartingNewPlayer */
	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) final;

	/** SpawnDefaultPawnAtTransform */
	virtual APawn* SpawnDefaultPawnAtTransform_Implementation(AController* NewPlayer, const FTransform& SpawnTransform) final;

	/*
	* member methods
	*/
	void HandleMatchAssignmentIfNotExpectingOne();
	void OnMatchAssignmentGiven(FPrimaryAssetId ExperienceId);
	bool IsExperienceLoaded() const;
	void OnExperienceLoaded(const UJhExperienceDefinition* CurrentExperience);

	const UJhPawnData* GetPawnDataForController(const AController* InController) const;
};
