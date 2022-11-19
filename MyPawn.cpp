// (c) Andrew Pol aka BonaMors


#include "MyPawn.h"



AMyPawn::AMyPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));

	PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Player Mesh"));
	PlatformMesh->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Static Camera"));
	Camera->SetupAttachment(RootComponent);

	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Move Component"));

	SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
}


void AMyPawn::BeginPlay()
{
	Super::BeginPlay();

	CameraLocation = Camera->GetComponentLocation();
}


void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Attach cameta to initial location (can be unpinned or rewrite just to not do using tick function)
	if (Camera->GetComponentLocation() != CameraLocation)
	{
		Camera->SetWorldLocation(CameraLocation);
	}
}


void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


