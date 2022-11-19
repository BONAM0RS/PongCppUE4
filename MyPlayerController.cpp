// (c) Andrew Pol aka BonaMors


#include "Net/UnrealNetwork.h"
#include "MyPlayerController.h"


AMyPlayerController::AMyPlayerController()
{
	bShowMouseCursor = false;
	bEnableClickEvents = false;

	MoveSpeed = 30;
}


void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();
}


void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis(TEXT("MoveLR"), this, &AMyPlayerController::MoveLR);
}


void AMyPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AMyPlayerController::MoveLR(float Value)
{
	if (GetPawn())
	{
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		Value = FMath::Clamp(Value, -1.0f, 1.0f) * MoveSpeed;

		if (LeaveGateBorders(Direction, Value) == false)
		{
			GetPawn()->AddMovementInput(Direction, Value);
		}
	}

	if (GetNetMode() == NM_DedicatedServer)
	{
		return;
	}

	if (GetLocalRole() == ROLE_AutonomousProxy)
	{
		if (GetPawn())
		{
			UpdatePawnLocationOnServer(GetPawn()->GetActorLocation());
		}
	}
}


void AMyPlayerController::UpdatePawnLocationOnServer_Implementation(FVector Location)
{
	GetPawn()->SetActorLocation(Location);
}


bool AMyPlayerController::LeaveGateBorders(FVector Dir, float Val)
{
	PlayerLocation = GetPawn()->GetActorLocation();

	if (Dir.Y == -1)
	{
		if ((PlayerLocation.Y > 2100 && Val < 0) || (PlayerLocation.Y < -2100 && Val > 0))
		{
			return true;
		}
	}
	else if (Dir.Y == 1)
	{
		if ((PlayerLocation.Y > 2100 && Val > 0) || (PlayerLocation.Y < -2100 && Val < 0))
		{
			return true;
		}
	}

	return false;
}







