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

	/* Pawn의 Class, 어떤 Pawn을 소환할 지 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Jh|Pawn")
	TSubclassOf<APawn> PawnClass;
};
