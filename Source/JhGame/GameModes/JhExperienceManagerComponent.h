// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/GameStateComponent.h"
#include "JhExperienceManagerComponent.generated.h"

class UJhExperienceDefinition;

enum class EJhExperienceLoadState
{
	Unloaded,
	Loading,
	Loaded,
	Deativating, // 로딩 해제 단계
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnJhExperienceLoaded, const UJhExperienceDefinition*);

/**
 * UJhExperienceManagerComponent
 * - 말 그대로, 해당 Comp는 Game State를 Owner로 가지면서, Experience의 상태 정보를 가지고 있는 Comp이다
 * - 뿐만 아니라, Manager라는 단어가 포함되어 있듯이, Experience 로딩 상태 업데이트 및 이벤트를 관리한다
 */
UCLASS()
class JHGAME_API UJhExperienceManagerComponent : public UGameStateComponent
{
	GENERATED_BODY()

public:
	/*
	* member methods
	*/
	bool IsExperienceLoaded() { return (EJhExperienceLoadState::Loaded == LoadState) && (nullptr != CurrentExperience); }
	
	/* 아래의 OnExperienceLoaded에 바인딩하거나, 이미 Experience 로딩이 완료되었다면 바로 호출함 */
	void CallOrRegister_OnExperienceLoaded(FOnJhExperienceLoaded::FDelegate&& Delegate);

	void ServerSetCurrentExperience(FPrimaryAssetId ExperienceId);
	void StartExperienceLoad();
	void OnExperienceLoadComplete();
	void OnExperienceFullLoadCompleted();

	const UJhExperienceDefinition* GetCurrentExperienceChecked() const;
public:
	UPROPERTY()
	TObjectPtr<const UJhExperienceDefinition> CurrentExperience;

	/* Experience의 로딩 상태 모니터링 */
	EJhExperienceLoadState LoadState = EJhExperienceLoadState::Unloaded;

	/* Expreience 로딩 완료된 이후, Broadcasting Delegate */
	FOnJhExperienceLoaded OnExperienceLoaded;

};
