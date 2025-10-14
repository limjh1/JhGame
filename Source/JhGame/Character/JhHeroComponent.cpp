// Fill out your copyright notice in the Description page of Project Settings.


#include "JhHeroComponent.h"

UJhHeroComponent::UJhHeroComponent(const FObjectInitializer& ObjectInitalizer)
	: Super(ObjectInitalizer)
{
	PrimaryComponentTick.bStartWithTickEnabled = false;
	PrimaryComponentTick.bCanEverTick = false;
}
