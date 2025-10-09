// Fill out your copyright notice in the Description page of Project Settings.


#include "JhPlayerState.h"
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

}