// Fill out your copyright notice in the Description page of Project Settings.

#include "JhGameModeBase.h"
#include "JhExperienceManagerComponent.h"
#include "JhGameState.h"
#include "JhGame/Character/JhCharacter.h"
#include "JhGame/Player/JhPlayerController.h"
#include "JhGame/Player/JhPlayerState.h"
#include "JhGame/JhLogChannels.h"
#include "JhGame/GameModes/JhExperienceDefinition.h"
#include "JhGame/Character/JhPawnData.h"

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

	// 해당 시점에서는 GameState가 있다는 것을 보장받을 수 있으나 검사.
	check(GameState);

	// Experience 비동기 로딩을 위한 Delegate를 준비한다:
	UJhExperienceManagerComponent* ExperienceManagerComponent = GameState->FindComponentByClass<UJhExperienceManagerComponent>();
	check(ExperienceManagerComponent);

	// OnExperienceLoaded 등록
	ExperienceManagerComponent->CallOrRegister_OnExperienceLoaded(FOnJhExperienceLoaded::FDelegate::CreateUObject(this, &ThisClass::OnExperienceLoaded));
}

UClass* AJhGameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	// GetPawnDataForController를 활용하여, PawnData로부터 PawnClass를 유도하자
	if (const UJhPawnData* PawnData = GetPawnDataForController(InController))
	{
		if (PawnData->PawnClass)
		{
			return PawnData->PawnClass;
		}
	}

	return Super::GetDefaultPawnClassForController_Implementation(InController);
}

PRAGMA_DISABLE_OPTIMIZATION
void AJhGameModeBase::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{	
	// 로드가 되었을 때만 호출하게되면, SpawnDefaultPawnAtTransform_Implementation 타이밍에, 지정한 데이터로 스폰할 것을 보장받을 수 있다.
	if (IsExperienceLoaded())
	{
		Super::HandleStartingNewPlayer_Implementation(NewPlayer);
	}	
}
PRAGMA_ENABLE_OPTIMIZATION

APawn* AJhGameModeBase::SpawnDefaultPawnAtTransform_Implementation(AController* NewPlayer, const FTransform& SpawnTransform)
{
	UE_LOG(LogJh, Log, TEXT("SpawnDefaultPawnAtTransform_Implementation is called!"));

	return Super::SpawnDefaultPawnAtTransform_Implementation(NewPlayer, SpawnTransform);
}

void AJhGameModeBase::HandleMatchAssignmentIfNotExpectingOne()
{
	// 해당 함수에서는 우리가 로딩할 Experience에 대해 PrimaryAssetId를 생성하여, OnMatchAssignmentGiven으로 넘겨준다

	FPrimaryAssetId ExperienceId;

	// precedence order (highest wins)
	// - matchmaking assignment (if present)
	// - default experience

	// 라이라 원본에서는 기본값세팅해서 되기 전에, 굉장히 많은 경로로 만들어냄. 그래서 결국 ExperienceId가 유효한 값이 아닌경우에만 기본값을 세팅함.

	UWorld* World = GetWorld();

	// fall back to the default experience
	// 일단 기본 옵션으로 default하게 B_JhDefaultExperience로 설정놓자
	if (!ExperienceId.IsValid())
	{
		ExperienceId = FPrimaryAssetId(FPrimaryAssetType("JhExperienceDefinition"), FName("B_JhDefaultExperience"));
	}

	// 필자가 이해한 HandleMatchAssignmentIfNotExpectingOne과 OnMatchAssignmentGiven()은 아직 직관적으로 이름이 와닫지 않는다고 생각한다
	// - 후일, 어느정도 Lyra가 구현되면, 해당 함수의 명을 더 이해할 수 있을 것으로 예상한다
	OnMatchAssignmentGiven(ExperienceId);
}

void AJhGameModeBase::OnMatchAssignmentGiven(FPrimaryAssetId ExperienceId)
{
	// 해당 함수는 ExperienceManagerComponent을 활용하여 Experience을 로딩하기 위해, ExperienceManagerComponent의 ServerSetCurrentExperience를 호출한다

	check(ExperienceId.IsValid());

	UJhExperienceManagerComponent* ExperienceManagerComponent = GameState->FindComponentByClass<UJhExperienceManagerComponent>();
	check(ExperienceManagerComponent);
	ExperienceManagerComponent->ServerSetCurrentExperience(ExperienceId); // Dedicated Server
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
	// PlayerController를 순회하며
	for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
	{
		APlayerController* PC = Cast<APlayerController>(*Iterator);

		// PlayerController가 Pawn을 Possess하지 않았다면, RestartPlayer를 통해 Pawn을 다시 Spawn한다
		// - 한번 OnPossess를 보도록 하자:
		if (PC && PC->GetPawn() == nullptr)
		{
			if (PlayerCanRestart(PC))
			{
				RestartPlayer(PC);
			}
		}
	}
}

const UJhPawnData* AJhGameModeBase::GetPawnDataForController(const AController* InController) const
{
	// 게임 도중에 PawnData가 오버라이드 되었을 경우, PawnData는 PlayerState에서 가져오게 됨
	if (InController)
	{
		if (const AJhPlayerState* JhPS = InController->GetPlayerState<AJhPlayerState>())
		{
			// GetPawnData 구현
			if (const UJhPawnData* PawnData = JhPS->GetPawnData<UJhPawnData>())
			{
				return PawnData;
			}
		}
	}

	// fall back to the default for the current experience
	// 아직 PlayerState에 PawnData가 설정되어 있지 않은 경우, ExperienceManagerComponent의 CurrentExperience로부터 가져와서 설정
	check(GameState);
	UJhExperienceManagerComponent* ExperienceManagerComponent = GameState->FindComponentByClass<UJhExperienceManagerComponent>();
	check(ExperienceManagerComponent);

	if (ExperienceManagerComponent->IsExperienceLoaded())
	{
		// GetExperienceChecked 구현
		const UJhExperienceDefinition* Experience = ExperienceManagerComponent->GetCurrentExperienceChecked();
		if (Experience->DefaultPawnData)
		{
			return Experience->DefaultPawnData;
		}
	}

	// 어떠한 케이스에도 핸들링 안되었으면 nullptr
	return nullptr;
}
