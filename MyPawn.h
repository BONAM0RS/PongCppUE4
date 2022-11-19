// (c) Andrew Pol aka BonaMors

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "GameFramework/FloatingPawnMovement.h"
#include "Camera/CameraComponent.h"

#include "MyPawn.generated.h"


UCLASS()
class PONG_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:	
	AMyPawn();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly)
		UStaticMeshComponent* PlatformMesh;

	UPROPERTY(EditDefaultsOnly)
		UCameraComponent* Camera;

	UPROPERTY(EditDefaultsOnly)
		UFloatingPawnMovement* FloatingPawnMovement;

	FVector CameraLocation;
};
