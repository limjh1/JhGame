// Copyright Epic Games, Inc. All Rights Reserved.

#include "JhGame.h"
#include "JhLogChannels.h"
#include "Modules/ModuleManager.h"

class FJhGameModule : public FDefaultGameModuleImpl
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

IMPLEMENT_PRIMARY_GAME_MODULE(FJhGameModule, JhGame, "JhGame" );

void FJhGameModule::StartupModule()
{
	FDefaultGameModuleImpl::StartupModule();
	UE_LOG(LogJh, Warning, TEXT("FJhGameModule"));
}

void FJhGameModule::ShutdownModule()
{
	FDefaultGameModuleImpl::ShutdownModule();
}
