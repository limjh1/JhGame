// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "JhPawnData.generated.h"

/**
 * 
 */
UCLASS()
class JHGAME_API UJhPawnData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UJhPawnData(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};
