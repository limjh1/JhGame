// Fill out your copyright notice in the Description page of Project Settings.


#include "JhPlayerState.h"
#include "JhGame/GameModes/JhGameModeBase.h"
#include "JhGame/GameModes/JhExperienceManagerComponent.h"


void AJhPlayerState::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	const AGameStateBase* GameState = GetWorld()->GetGameState();
	check(GameState);

	UJhExperienceManagerComponent* ExperienceManagerComponent = GameState->FindComponentByClass<UJhExperienceManagerComponent>();
	check(ExperienceManagerComponent);

	ExperienceManagerComponent->CallOrRegister_OnExperienceLoaded(FOnJhExperienceLoaded::FDelegate::CreateUObject(this, &ThisClass::OnExperienceLoaded));
}

void AJhPlayerState::OnExperienceLoaded(const UJhExperienceDefinition* CurrentExperience)
{
	if (AJhGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AJhGameModeBase>())
	{
		// AJhGameMode에서 GetPawnDataForController를 구현해야 함
		// - GetPawnDataForController에서 우리는 아직 PawnData를 설정하지 않았으므로, ExperienceMangerComponent의 DefaultPawnData로 설정한다
		const UJhPawnData* NewPawnData = GameMode->GetPawnDataForController(GetOwningController());
		check(NewPawnData);

		SetPawnData(NewPawnData);
	}
}

void AJhPlayerState::SetPawnData(const UJhPawnData* InPawnData)
{
	check(InPawnData);

	// PawnData가 두번 설정되는 것은 원하지 않음!
	check(!PawnData);

	PawnData = InPawnData;
}
