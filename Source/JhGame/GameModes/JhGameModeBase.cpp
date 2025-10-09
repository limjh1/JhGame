// Fill out your copyright notice in the Description page of Project Settings.

#include "JhGameModeBase.h"
#include "JhExperienceManagerComponent.h"
#include "JhGameState.h"
#include "JhGame/Character/JhCharacter.h"
#include "JhGame/Player/JhPlayerController.h"
#include "JhGame/Player/JhPlayerState.h"
#include "JhGame/JhLogChannels.h"

AJhGameModeBase::AJhGameModeBase()
{
	GameStateClass = AJhGameState::StaticClass();
	PlayerControllerClass = AJhPlayerController::StaticClass();
	PlayerStateClass = AJhPlayerState::StaticClass();
	DefaultPawnClass = AJhCharacter::StaticClass();
}

void AJhGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	// 아직 GameInstance를 통해, 초기화 작업이 진행되므로, 현 프레임에는 Lyra의 Concept인 Experience 처리를 진행할 수 없다:
	// - 이를 처리하기 위해, 한프레임 뒤에 이벤트를 받아 처리를 이어서 진행한다
	GetWorld()->GetTimerManager().SetTimerForNextTick(this, &ThisClass::HandleMatchAssignmentIfNotExpectingOne);

}

void AJhGameModeBase::InitGameState()
{
	Super::InitGameState();

	// 해당 시점에서는 GameState가 있다는 것을 보장받을 수 있음.

	// Experience 비동기 로딩을 위한 Delegate를 준비한다:
	UJhExperienceManagerComponent* ExperienceManagerComponent = GameState->FindComponentByClass<UJhExperienceManagerComponent>();
	check(ExperienceManagerComponent);

	// OnExperienceLoaded 등록
	ExperienceManagerComponent->CallOrRegister_OnExperienceLoaded(FOnJhExperienceLoaded::FDelegate::CreateUObject(this, &ThisClass::OnExperienceLoaded));
}

void AJhGameModeBase::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{	
	if (IsExperienceLoaded())
	{
		Super::HandleStartingNewPlayer_Implementation(NewPlayer);
	}	
}

APawn* AJhGameModeBase::SpawnDefaultPawnAtTransform_Implementation(AController* NewPlayer, const FTransform& SpawnTransform)
{
	UE_LOG(LogJh, Log, TEXT("SpawnDefaultPawnAtTransform_Implementation is called!"));

	return Super::SpawnDefaultPawnAtTransform_Implementation(NewPlayer, SpawnTransform);
}

void AJhGameModeBase::HandleMatchAssignmentIfNotExpectingOne()
{
	
}

bool AJhGameModeBase::IsExperienceLoaded() const
{
	check(GameState);
	UJhExperienceManagerComponent* ExperienceManagerComponent = GameState->FindComponentByClass<UJhExperienceManagerComponent>();
	check(ExperienceManagerComponent);

	return ExperienceManagerComponent->IsExperienceLoaded();
}

void AJhGameModeBase::OnExperienceLoaded(const UJhExperienceDefinition* CurrentExperience)
{

}
