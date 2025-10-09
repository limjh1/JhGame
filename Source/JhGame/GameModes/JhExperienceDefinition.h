// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "JhExperienceDefinition.generated.h"

class UJhPawnData;

/**
 * 
 */
UCLASS()
class JHGAME_API UJhExperienceDefinition : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UJhExperienceDefinition(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	/**
	 * member variables
	 */
	UPROPERTY(EditDefaultsOnly, Category = Gameplay)
	TObjectPtr<UJhPawnData> DefaultPawnData;

	/**
	 * 해당 property는 단순히 마킹 및 기억용으로 남겨둔다
	 * - 게임 모드에 따른 GameFeature plugin을 로딩하는데 이에 대한 연결고리고 생각하면 된다
	 * - 후일 ShooterCore 관련 Plugin 작업할 경우, 진행하게 될 예정이다
	 */
	UPROPERTY(EditDefaultsOnly, Category = Gameplay)
	TArray<FString> GameFeaturesToEnable;

};
