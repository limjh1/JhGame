// Fill out your copyright notice in the Description page of Project Settings.


#include "JhGameState.h"
#include "JhGame/GameModes/JhExperienceManagerComponent.h"

AJhGameState::AJhGameState()
{
	ExperienceManagerComponent = CreateDefaultSubobject<UJhExperienceManagerComponent>(TEXT("ExperienceManagerComponent"));
}
