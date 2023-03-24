// Fill out your copyright notice in the Description page of Project Settings.


#include "ACharacter.h"
#include "Kismet/KismetMathLibrary.h"

AACharacter::AACharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationYaw = true;

	arm = CreateDefaultSubobject<USpringArmComponent>("Arm");
	camera = CreateDefaultSubobject<UCameraComponent>("Camera");

	arm->SetupAttachment(RootComponent);
	camera->SetupAttachment(arm);

}

bool AACharacter::IsPossess()
{
	return isControlled;
}

void AACharacter::SetSpeedWalk(float _speed)
{
	speed = _speed;
}

void AACharacter::BeginPlay()
{
	Super::BeginPlay();

}

void AACharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ShowDebug();
	MoveToNextPath();

}

void AACharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Vertical", this, &AACharacter::MoveForward);
	PlayerInputComponent->BindAxis("Rotation", this, &AACharacter::Rotate);
	

}

void AACharacter::MoveForward(float _axis)
{
	if (!isControlled) return;
	AddMovementInput(GetActorForwardVector() * _axis);
}
void AACharacter::Rotate(float _axis)
{
	if (!isControlled) return;
	AddControllerYawInput(_axis);
}

void AACharacter::MoveToNextPath()
{
	if (isControlled) return;
	if (pathPointNumber + 1>= pathFinding.Num()) {
		Destroy();
		return;
	}

	const FVector _target = pathFinding[pathPointNumber + 1];
	FVector _nextPoint = _target + FVector(0, 0, GetActorLocation().Z);
	const FVector _thisLoc = GetActorLocation();

	const FRotator _rotation = UKismetMathLibrary::FindLookAtRotation(_thisLoc, _nextPoint);
	SetActorRotation(_rotation);

	const FVector _location = FMath::VInterpConstantTo(_thisLoc, _nextPoint, GetWorld()->DeltaTimeSeconds, speed * 100);
	SetActorLocation(_location);

	if (GetActorLocation() == _nextPoint) {
		pathPointNumber++;
	}
}

void AACharacter::ShowDebug()
{
	size_t _size = pathFinding.Num();
	for (size_t i = 0; i < _size; i++)
	{
		DRAW_SPHERE(pathFinding[i], 20, 20, FColor::Red, 2);
		if (i == 0) continue;
		DRAW_LINE(pathFinding[i - 1], pathFinding[i], FColor::Red, 2);
	}

	for (size_t i = 0; i < _size; i++) {
		const FVector _nextPoint = pathFinding[i];
		DRAW_TEXT(_nextPoint, _nextPoint.ToCompactString(), FColor::Blue, 1);
	}

}

