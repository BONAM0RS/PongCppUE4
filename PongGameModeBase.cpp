// Copyright Epic Games, Inc. All Rights Reserved.
// (c) Andrew Pol aka BonaMors


#include "PongGameModeBase.h"

#include "EngineUtils.h"
#include "GameFramework/PlayerStart.h"
#include "MyActor.h"
#include "Engine/GameEngine.h"


void APongGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
	UE_LOG(LogTemp, Warning, TEXT("Game is running: %s %s"), *MapName, *Options);

	// Calculate and add Player Start points to array
	for (TActorIterator<APlayerStart> It(GetWorld()); It; ++It)
	{
		FreePlayerStarts.Add(*It);
		UE_LOG(LogTemp, Warning, TEXT("Found player start: %s"), *(*It)->GetName());
	}
}


void APongGameModeBase::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	if (FreePlayerStarts.Num() == 0)
	{
		ErrorMessage = TEXT("Server full");
	}

	Super::PreLogin(Options, Address, UniqueId, ErrorMessage);
}


FString APongGameModeBase::InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId, const FString& Options, const FString& Portal)
{
	if (FreePlayerStarts.Num() == 0)
	{
		UE_LOG(LogTemp, Log, TEXT("No free player starts in InitNewPlayer"));
		return FString(TEXT("No free player starts"));
	}

	// Choose start spot for new player
	NewPlayerController->StartSpot = FreePlayerStarts.Pop();
	UE_LOG(LogTemp, Warning, TEXT("Using player start %s for %s"), *NewPlayerController->StartSpot->GetName(), *NewPlayerController->GetName());

	// Show waiting 2nd player text
	if (GetNumPlayers() == 1)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Waiting for 2nd player.."));
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Waiting for 2nd player.."));
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Waiting for 2nd player.."));
		}	
	}

	// Launch ball when 2nd player connected
	if (GetNumPlayers() == 2)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Two players are enough. Let's play!"));
		}

		for (TActorIterator<AMyActor> It(GetWorld()); It; ++It)
		{
			It->Play();
		}
	}
	
	return Super::InitNewPlayer(NewPlayerController, UniqueId, Options, Portal);
}

