// (c) Andrew Pol aka BonaMors

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "MyPlayerController.generated.h"


/**
 * 
 */
UCLASS()
class PONG_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AMyPlayerController();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupInputComponent() override;

private:

	void MoveLR(float Value);

	bool LeaveGateBorders(FVector Dir, float Val);

	UFUNCTION(Server, Unreliable)
		void UpdatePawnLocationOnServer(FVector Location);

private:
	UPROPERTY(EditAnywhere)
		float MoveSpeed;

	FVector PlayerLocation;
};
