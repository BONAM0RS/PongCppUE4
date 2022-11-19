// Copyright Epic Games, Inc. All Rights Reserved.
// (c) Andrew Pol aka BonaMors

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "PongGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PONG_API APongGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;

	virtual FString InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId, const FString& Options, 
		const FString& Portal = TEXT("")) override;

private:
	TArray<class APlayerStart*> FreePlayerStarts;
};
