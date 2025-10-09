// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "JhUserFacingExperience.generated.h"

/**
 * 
 */
UCLASS()
class JHGAME_API UJhUserFacingExperience : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UJhUserFacingExperience(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	/** the specific map to load */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Experience, meta = (AllowedTypes = "Map"))
	FPrimaryAssetId MapID;

	/** the gameplay expierence to load */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Experience, meta = (AllowedTypes = "JhExperienceDefinition"))
	FPrimaryAssetId ExperienceID;
};
