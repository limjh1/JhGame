// Fill out your copyright notice in the Description page of Project Settings.


#include "JhCharacter.h"
#include "JhPawnExtensionComponent.h"

// Sets default values
AJhCharacter::AJhCharacter()
{
	PrimaryActorTick.bStartWithTickEnabled = false;
	PrimaryActorTick.bCanEverTick = false;

	// PawnExtComponent 생성
	PawnExtComponent = CreateDefaultSubobject<UJhPawnExtensionComponent>(TEXT("PawnExtensionComponent"));

}

// Called when the game starts or when spawned
void AJhCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AJhCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AJhCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

